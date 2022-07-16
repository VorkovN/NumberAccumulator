#include <iostream>

#include "ClientFacade.h"
#include "ClientTransport.h"
#include "ClientSettings.h"
#include "ClientSettingsParser.h"

void sig_handler(int sig)
{
    apps::client::ClientTransport::_sigIntReceived = true;
}

int main(int argc, char** argv)
{
    auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv);
    if (!settingsOpt) return 0;
    apps::client::ClientSettings settings = settingsOpt.value();

    apps::client::ClientFacade facade(std::move(settings));
    facade.start();

    return 0;
}
