#include "ServerFacade.h"

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
            libs::NumbersParser::countNumbersInString(receivedDataOpt.value().sendData);
            transport->send(receivedDataOpt.value());
        }
    }
}