#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H

#include <netinet/in.h>

#include <Interfaces/ITransport.h>


namespace apps::client
{

    class ClientTcpTransport: public interface::ITransport
    {
    public:
        ClientTcpTransport(std::string&& serverIp, uint32_t serverPort);
        ~ClientTcpTransport();
        void receive() override;
        void send(const std::string& data) override;

    private:
        int _socketFd;
        sockaddr_in _socketAddress;
        const std::string _serverIp;
        const uint32_t _serverPort;
        socklen_t _socketAddressSize;
    };

}

#endif
