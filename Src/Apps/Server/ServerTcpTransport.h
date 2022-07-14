#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::server
{

    class ServerTcpTransport: public interface::ITransport
    {
    public:
        ServerTcpTransport(std::string&& selfIp, uint32_t selfPort);
        void init() override;
        void receive(const std::string& sendData) override;
        void send(const std::string& data) override;

    private:
        const std::string _selfIp;
        const uint32_t _selfPort;
    };

}

#endif
