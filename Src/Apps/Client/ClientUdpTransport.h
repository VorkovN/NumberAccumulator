#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::client
{

    class ClientUdpTransport: public interface::ITransport
    {
    public:
        void init() override;
        void receive(const std::string& sendData) override;
        void send(const std::string& data) override;
    };

}

#endif
