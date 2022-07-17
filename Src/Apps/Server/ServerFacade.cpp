#include "ServerFacade.h"

#include <thread>

#include <Libs/NumberParser.h>

#include "ServerTcpTransport.h"
#include "ServerUdpTransport.h"

namespace apps::server
{

    ServerFacade::ServerFacade(ServerSettings&& settings)
    {
        _udpTransport =  std::make_unique<ServerUdpTransport>(std::move(settings.udpSelfIp), settings.udpSelfPort);
        _tcpTransport =  std::make_unique<ServerTcpTransport>(std::move(settings.tcpSelfIp), settings.tcpSelfPort);
    }

    void ServerFacade::start()
    {
        _udpTransport->start();
        std::thread(&ServerTransport::start, _udpTransport.get()).detach();
        _tcpTransport->start();
    }
}