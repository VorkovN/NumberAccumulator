#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H

#include <netinet/in.h>
#include <optional>
#include <string>

namespace apps::client
{

    class ClientTransport
    {
    public:
        ClientTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ClientTransport();
        virtual void init() = 0;
        virtual std::optional<std::string> receive() = 0;
        virtual void send(const std::string& sendData) = 0;

    protected:
        int _socketFd;
        sockaddr_in _socketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _socketAddressSize;

    };

}

#endif
