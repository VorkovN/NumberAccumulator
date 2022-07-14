#include "ServerFacade.h"
#include "ServerSettings.h"
#include "ServerSettingsParser.h"


int main(int argc, char** argv)
{
    auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv);
    if (!settingsOpt) return 0;
    apps::server::ServerSettings settings = settingsOpt.value();

    apps::server::ServerFacade facade(std::move(settings));
    facade.start();

    return 0;
}
