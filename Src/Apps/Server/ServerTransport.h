#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H

#include <any>
#include <netinet/in.h>
#include <optional>
#include <string>

namespace apps::server
{

    class ServerTransport
    {
    public:
        struct MiddleLayerData
        {
            std::string sendData;
            std::any peerInformation;
        };

    public:
        ServerTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ServerTransport();
        virtual void init() = 0;
        virtual std::optional<MiddleLayerData> receive() = 0;
        virtual void send(MiddleLayerData middleLayerData) = 0;

    protected:
        int _serverSocketFd;
        sockaddr_in _serverSocketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _serverSocketAddressSize;
    };

}

#endif
