#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H

#include <netinet/in.h>

#include "ClientTransport.h"


namespace apps::client
{

    class ClientTcpTransport: public ClientTransport
    {
    public:
        ClientTcpTransport(std::string&& serverIp, uint32_t serverPort);
        ~ClientTcpTransport();
        void receive() override;
        void send(const std::string& data) override;

    };

}

#endif
