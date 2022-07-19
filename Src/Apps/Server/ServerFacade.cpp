#include "ServerFacade.h"

#include <numeric>
#include <set>
#include <sstream>
#include <thread>

#include <Libs/NumberParser.h>

#include "ServerTcpTransport.h"
#include "ServerUdpTransport.h"

namespace apps::server
{
    bool ServerFacade::_sigIntReceived = false;

    ServerFacade::ServerFacade(ServerSettings&& settings)
    {
        _udpTransport =  std::make_unique<ServerUdpTransport>(std::move(settings.udpSelfIp), settings.udpSelfPort);
        _tcpTransport =  std::make_unique<ServerTcpTransport>(std::move(settings.tcpSelfIp), settings.tcpSelfPort);
    }

    void ServerFacade::start()
    {
        std::thread(&ServerFacade::handleReceivedConnection, this, _udpTransport.get()).detach();
        handleReceivedConnection(_tcpTransport.get());
    }

    void ServerFacade::handleReceivedConnection(ServerTransport* transport)
    {
        while (!_sigIntReceived)
        {
            auto receivedDataOpt = transport->receive();
            if (!receivedDataOpt.has_value())
                continue;
            std::string answer = countNumbersInString(receivedDataOpt.value().sendData);
            transport->send({answer, receivedDataOpt.value().peerInformation});
        }
    }

    std::string ServerFacade::countNumbersInString(std::string_view inputString)
    {
        auto sortedNumbers = libs::NumbersParser::getNumbersFromString(inputString);
        int sum = std::accumulate(sortedNumbers.begin(), sortedNumbers.end(), 0);
        std::string answer = makeAnswerString(std::move(sortedNumbers), sum);
        return answer;
    }

    std::string ServerFacade::makeAnswerString(std::set<int>&& nums, int sum)
    {
        std::stringstream answer;
        for(auto elem: nums)
            answer << elem << ' ';
        answer << '\n' << sum << '\n';

        return answer.str();
    }
}