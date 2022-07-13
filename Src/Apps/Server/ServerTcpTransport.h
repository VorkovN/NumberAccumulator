#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERTCPTRANSPORT_H

#include <Interfaces/ITransport.h>

namespace apps::server
{

    class ServerTcpTransport: public interface::ITransport
    {
    public:
        void init() override;
        void receive(const std::string& sendData) override;
        void send(const std::string& data) override;
    };

}

#endif
