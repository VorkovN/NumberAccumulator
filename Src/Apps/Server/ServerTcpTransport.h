#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H

#include "ServerTransport.h"

#include <map>
#include <sys/epoll.h>

namespace apps::server
{

    class ServerTcpTransport: public ServerTransport
    {
    public:
        ServerTcpTransport(std::string&& selfIp, uint32_t selfPort);
        ~ServerTcpTransport() override;
        void init() override;
        std::optional<MiddleLayerData> receive() override;
        void send(MiddleLayerData middleLayerData) override;

    private:
        int _epoll;
        std::map<int, epoll_event> _events;
    };

}

#endif
