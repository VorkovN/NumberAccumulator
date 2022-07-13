#include "ClientFacade.h"
#include "ClientSettings.h"
#include "ClientSettingsParser.h"


int main() {

    //TODO сделать парсинг
    apps::client::ClientSettings settings{};

    apps::client::ClientFacade facade(std::move(settings));
    facade.start();

    return 0;
}
