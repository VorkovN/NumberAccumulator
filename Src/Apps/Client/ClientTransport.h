#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H

#include <netinet/in.h>
#include <string>

//#include <Interfaces/ITransport.h>

namespace apps::client
{

    class ClientTransport
    {
    public:
        ClientTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ClientTransport();
        void start();
        virtual void send(const std::string& data) = 0;
        virtual void receive() = 0;

    public:
        static bool _sigIntReceived;

    protected:
        int _socketFd;
        sockaddr_in _socketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _socketAddressSize;
    };

}

#endif
