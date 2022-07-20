#include <csignal>

#include <ClientFacade.h>
#include <ClientSettings.h>
#include <ClientSettingsParser.h>

void sig_handler(int sig)
{
    apps::client::ClientFacade::_needToKillProgram = true;
}

int main(int argc, char** argv)
{
    signal(SIGINT, sig_handler);

    auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv);
    if (!settingsOpt) return 0;
    apps::client::ClientSettings settings = settingsOpt.value();

    apps::client::ClientFacade facade(std::move(settings));
    facade.start();

    return 0;
}
