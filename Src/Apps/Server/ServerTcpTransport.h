#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H

#include "ServerTransport.h"

namespace apps::server
{

    class ServerTcpTransport: public ServerTransport
    {
    public:
        ServerTcpTransport(std::string&& selfIp, uint32_t selfPort);
        ~ServerTcpTransport() override;
        void receive() override;
//        void send(const std::string& data) override;
        void send(const std::string& data, int peerSocketFd);

    };

}

#endif
