#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTTCPTRANSPORT_H

#include <netinet/in.h>
#include <optional>
#include <string>

#include "ClientTransport.h"

namespace apps::client
{

    class ClientTcpTransport: public ClientTransport
    {
    public:
        ClientTcpTransport(std::string&& serverIp, uint32_t serverPort);
        ~ClientTcpTransport() override;
        void init() override;
        std::optional<std::string> receive() override;
        bool send(const std::string& sendData) override;
    };

}

#endif
