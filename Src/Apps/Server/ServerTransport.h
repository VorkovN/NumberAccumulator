#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTRANSPORT_H

#include <netinet/in.h>

#include <string>

//#include <Interfaces/ITransport.h>

namespace apps::server
{

    class ServerTransport
    {
    public:
        ServerTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ServerTransport();
        void start();
        virtual void receive() = 0;

    public:
        static bool _sigIntReceived;

    protected:
        int _serverSocketFd;
        sockaddr_in _serverSocketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _serverSocketAddressSize;
    };

}

#endif
