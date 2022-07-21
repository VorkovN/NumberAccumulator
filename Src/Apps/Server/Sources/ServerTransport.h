#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H

#include <any>
#include <netinet/in.h>
#include <optional>
#include <string>

#include "IServerTransport.h"

namespace apps::server
{

    class ServerTransport: public IServerTransport
    {

    public:
        ServerTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ServerTransport();

    protected:
        int _serverSocketFd;
        sockaddr_in _serverSocketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _serverSocketAddressSize;
    };

}

#endif
