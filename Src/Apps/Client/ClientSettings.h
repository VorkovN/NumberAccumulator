#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTSETTINGS_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTSETTINGS_H

#include <string>

namespace apps::client
{

    struct ClientSettings
    {
        enum Transport: bool {TCP, UDP};

        std::string serverIp;
        uint32_t serverPort;
        Transport transport;
    };

}
#endif
