#include "ServerFacade.h"
#include "ServerSettings.h"
#include "ServerSettingsParser.h"


int main() {

    //TODO сделать парсинг
    apps::server::ServerSettings settings{};

    apps::server::ServerFacade facade(std::move(settings));
    facade.start();

    return 0;
}
