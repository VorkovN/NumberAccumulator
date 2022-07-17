#include <thread>
#include <unistd.h>
#include "ClientFacade.h"

#include "ClientTcpTransport.h"
#include "ClientUdpTransport.h"

namespace apps::client
{
    bool ClientFacade::_sigIntReceived = false;

    ClientFacade::ClientFacade(ClientSettings&& settings)
    {
        if (settings.transport)
            _transport =  std::make_unique<ClientUdpTransport>(std::move(settings.serverIp), settings.serverPort);
        else
            _transport =  std::make_unique<ClientTcpTransport>(std::move(settings.serverIp), settings.serverPort);
    }

    void ClientFacade::start()
    {
        std::thread(&ClientTransport::start, _transport.get()).detach();
        handleInput();
    }

    void ClientFacade::handleInput()
    {
        while (!_sigIntReceived)
            sleep(1);
    }
}