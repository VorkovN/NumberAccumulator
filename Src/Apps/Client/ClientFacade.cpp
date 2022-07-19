#include <thread>
#include <unistd.h>
#include <iostream>
#include "ClientFacade.h"

#include "ClientTcpTransport.h"
#include "ClientUdpTransport.h"

namespace apps::client
{
    bool ClientFacade::_needToKillProgram = false;

    ClientFacade::ClientFacade(ClientSettings&& settings)
    {
        if (settings.transport)
            _transport =  std::make_unique<ClientUdpTransport>(std::move(settings.serverIp), settings.serverPort);
        else
            _transport =  std::make_unique<ClientTcpTransport>(std::move(settings.serverIp), settings.serverPort);
    }

    void ClientFacade::start()
    {
        try
        {
            _transport->init();
        }
        catch (const std::exception& err)
        {
            std::cerr << err.what() << std::endl;
            return;
        }

        std::thread(&ClientFacade::handleReceive, this).detach();
        handleInput();
    }

    void ClientFacade::handleReceive()
    {
        while (!_needToKillProgram)
        {
            if (auto printDataOpt = _transport->receive(); printDataOpt.has_value())
                printServerAnswer(printDataOpt.value());
        }
    }

    void ClientFacade::printServerAnswer(const std::string &serverAnswer)
    {
        std::cout << serverAnswer << std::endl;
    }

    void ClientFacade::handleInput()
    {
        while (!_needToKillProgram)
        {
            std::cout << "Input your message: " << std::endl;
            std::string inputString;
            std::cin >> inputString;
            _transport->send(inputString);
        }
    }


}