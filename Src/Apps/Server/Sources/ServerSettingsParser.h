#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERSETTINGSPARSER_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERSETTINGSPARSER_H

#include <optional>

#include "ServerSettings.h"

namespace apps::server
{

    class ServerSettingsParser
    {
    public:
        static std::optional<ServerSettings> getSettings(int argc, char** argv);

    private:
        static void usage();
    };

}
#endif
