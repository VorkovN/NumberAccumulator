#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTRANSPORT_H

#include <netinet/in.h>

#include <Interfaces/ITransport.h>

namespace apps::client
{

    class ClientTransport: public interface::ITransport
    {
    public:
        ClientTransport(std::string&& serverIp, uint32_t serverPort);
        virtual ~ClientTransport();
        void init() override;
        void handleInput();

    protected:
        int _socketFd;
        sockaddr_in _socketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _socketAddressSize;
    public:
        static bool _sigIntReceived;
    };

}

#endif
