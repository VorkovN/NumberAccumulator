#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H

#include "ClientTransport.h"

namespace apps::client
{

    class ClientUdpTransport: public ClientTransport
    {
    public:
        ClientUdpTransport(std::string&& serverIp, uint32_t serverPort);
        ~ClientUdpTransport() override;
        void init() override;
        std::optional<std::string> receive() override;
        void send(const std::string& sendData) override;
    };

}

#endif
