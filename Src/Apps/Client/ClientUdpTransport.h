#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTUDPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::client
{

    class ClientUdpTransport: public interface::ITransport
    {
    public:
        ClientUdpTransport(std::string&& serverIp, uint32_t serverPort);
        void init() override;
        void receive(const std::string& sendData) override;
        void send(const std::string& data) override;

    private:
        const std::string _serverIp;
        const uint32_t _serverPort;
    };

}

#endif
