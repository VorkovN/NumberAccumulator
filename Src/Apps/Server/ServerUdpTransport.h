#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERUDPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::server
{

    class ServerUdpTransport: public interface::ITransport
    {
    public:
        void init() override;
        void receive(const std::string& sendData) override;
        void send(const std::string& data) override;
    };

}

#endif