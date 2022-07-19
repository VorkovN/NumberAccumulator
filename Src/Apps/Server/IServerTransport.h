#ifndef NUMBERACCUMULATOR_APPS_SERVER_ISERVERTRANSPORT_H
#define NUMBERACCUMULATOR_APPS_SERVER_ISERVERTRANSPORT_H

#include <any>
#include <optional>
#include <vector>

namespace apps::server
{

    class IServerTransport
    {
    public:
        struct MiddleLayerData
        {
            std::string sendData;
            std::any peerInformation;
        };

    public:
        virtual void init() = 0;
        virtual std::optional<std::vector<MiddleLayerData>>receive() = 0;
        virtual bool send(MiddleLayerData middleLayerData) = 0;

    };
}

#endif