#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTSETTINGSPARSER_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTSETTINGSPARSER_H

#include <optional>

#include "ClientSettings.h"

namespace apps::client
{

class ClientSettingsParser
{
public:
    static std::optional<ClientSettings> getSettings(int argc, char** argv);

private:
    static void usage();
    static std::optional<ClientSettings::Transport> parseTransport(const std::string& transportStr);
};

}


#endif
