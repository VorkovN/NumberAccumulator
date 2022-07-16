#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::server
{

    class ServerUdpTransport: public interface::ITransport
    {
    public:
        ServerUdpTransport(std::string&& selfIp, uint32_t selfPort);
        void init() override;
        void receive() override;
        void send(const std::string& data) override;

    private:
        const std::string _selfIp;
        const uint32_t _selfPort;
    };

}

#endif
