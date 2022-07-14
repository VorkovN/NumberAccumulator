#include "ServerFacade.h"

#include <Libs/NumberParser.h>

#include "ServerTcpTransport.h"
#include "ServerUdpTransport.h"

namespace apps::server
{

    ServerFacade::ServerFacade(ServerSettings&& settings)
    {
            udpTransport =  std::make_unique<ServerUdpTransport>(std::move(settings.udpSelfIp), settings.udpSelfPort);
            tcpTransport =  std::make_unique<ServerTcpTransport>(std::move(settings.tcpSelfIp), settings.tcpSelfPort);
    }

    void ServerFacade::start()
    {

    }
}