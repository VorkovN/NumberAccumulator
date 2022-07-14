#include <iostream>

#include "ClientFacade.h"
#include "ClientSettings.h"
#include "ClientSettingsParser.h"



int main(int argc, char** argv)
{
    auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv);
    if (!settingsOpt) return 0;
    apps::client::ClientSettings settings = settingsOpt.value();

    apps::client::ClientFacade facade(std::move(settings));
    facade.start();

    return 0;
}
