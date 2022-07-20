#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H

#include <cinttypes>
#include <netinet/in.h>
#include <string>

#include "IClientTransport.h"

namespace apps::client
{

    class ClientTransport: public IClientTransport
    {
    public:
        ClientTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ClientTransport();

    protected:
        int _socketFd;
        sockaddr_in _socketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _socketAddressSize;

    };

}

#endif
