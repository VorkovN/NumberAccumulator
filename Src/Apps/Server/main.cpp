#include <csignal>

#include "ServerFacade.h"
#include "ServerTransport.h"
#include "ServerSettings.h"
#include "ServerSettingsParser.h"

void sig_handler(int sig)
{
    apps::server::ServerFacade::_needToKillProgram = true;
}

int main(int argc, char** argv)
{
    signal(SIGINT, sig_handler);

    auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv);
    if (!settingsOpt) return 0;
    apps::server::ServerSettings settings = settingsOpt.value();

    apps::server::ServerFacade facade(std::move(settings));
    facade.start();

    return 0;
}
