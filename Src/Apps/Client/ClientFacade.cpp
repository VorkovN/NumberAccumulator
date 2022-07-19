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
            auto printDataOpt = _transport->receive();
            if (!printDataOpt.has_value())
            {
                std::cerr << "Receive package error" << std::endl;
                continue;
            }

            if (printDataOpt.value().empty())
                _needToKillProgram = true; // если пришли пустые данные, значит это сигнал разрыва соединения

            printServerAnswer(printDataOpt.value());
        }
    }

    void ClientFacade::printServerAnswer(const std::string &serverAnswer)
    {
        std::cout << serverAnswer << std::endl;
    }

    void ClientFacade::handleInput()
    {
        // чтобы не учитывать пробелы в строке ввода
        while (!_needToKillProgram)
        {
            std::cout << "Input your message: " << std::endl;
            std::string inputString;
            std::getline(std::cin,inputString);

            bool sendingResult = _transport->send(inputString);
            if (!sendingResult)
                std::cerr << "Send package error" << std::endl;

            sleep(1); //можно и удалить, за это время успевает прийти ответ и отрисоваться на консоли
        }
    }

}