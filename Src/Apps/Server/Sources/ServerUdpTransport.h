#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H

#include "ServerTransport.h"

namespace apps::server
{

    class ServerUdpTransport: public ServerTransport
    {
    public:
        ServerUdpTransport(std::string&& selfIp, uint32_t selfPort);
        ~ServerUdpTransport() override;
        void init() override;
        std::optional<std::vector<IServerTransport::MiddleLayerData>> receive() override;
        bool send(MiddleLayerData middleLayerData) override;

    };

}

#endif
