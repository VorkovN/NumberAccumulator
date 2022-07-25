#include "ClientFacade.h"

#include <iostream>
#include <unistd.h>

#include "ClientTcpTransport.h"
#include "ClientUdpTransport.h"

namespace apps::client
{
    bool ClientFacade::_needToKillProgram = false;

    ClientFacade::ClientFacade(ClientSettings&& settings)
    {
        switch (settings.transport) {
            case ClientSettings::Transport::UDP :
            {
                _transport = std::make_unique<ClientUdpTransport>(std::move(settings.serverIp), settings.serverPort);
                break;
            }
            case ClientSettings::Transport::TCP :
            {
                _transport = std::make_unique<ClientTcpTransport>(std::move(settings.serverIp), settings.serverPort);
                break;
            }
            //TODO по идее нужно обработать дефолт и кинуть исключение
        }
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

        handleInput();
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
            std::getline(std::cin,inputString);
            if (_needToKillProgram)
                break;

            bool sendingResult = _transport->send(inputString);
            if (!sendingResult)
            {
                std::cerr << "Send package error" << std::endl;
                continue;
            }

            try {
                auto printDataOpt = _transport->receive();
                if (!printDataOpt.has_value()) {
                    _needToKillProgram = true;
                    break;
                }

                printServerAnswer(printDataOpt.value());

            }
            catch (const std::exception& err)
            {
                std::cerr << err.what() << std::endl;
                continue;
            }

        }
    }

}