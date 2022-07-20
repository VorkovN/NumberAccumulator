#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERSETTINGS_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERSETTINGS_H

#include <cinttypes>
#include <string>

namespace apps::server
{

struct ServerSettings
{
    std::string tcpSelfIp;
    uint32_t tcpSelfPort;

    std::string udpSelfIp;
    uint32_t udpSelfPort;
};

}


#endif
