#include "ClientFacade.h"

#include "ClientTcpTransport.h"
#include "ClientUdpTransport.h"

namespace apps::client
{

    ClientFacade::ClientFacade(ClientSettings&& settings)
    {
        if (settings.transport)
            transport =  std::make_unique<ClientUdpTransport>(std::move(settings.serverIp), settings.serverPort);
        else
            transport =  std::make_unique<ClientTcpTransport>(std::move(settings.serverIp), settings.serverPort);
    }

    void ClientFacade::start()
    {

    }
}