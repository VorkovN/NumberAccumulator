#ifndef NUMBERACCUMULATOR_APPS_CLIENT_ICLIENTTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_CLIENT_ICLIENTTRANSPORT_H

#include <optional>


namespace apps::client
{

    class IClientTransport
    {
    public:
        virtual void init() = 0;
        virtual std::optional<std::string> receive() = 0;
        virtual bool send(const std::string& sendData) = 0;

    };
}

#endif