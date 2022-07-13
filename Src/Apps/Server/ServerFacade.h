#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H

#include <Interfaces/ITransport.h>

#include "ServerSettings.h"

namespace apps::server
{

    class ServerFacade
    {
    public:
        explicit ServerFacade(ServerSettings&& settings);
        void start();

    private:

    };

}

#endif
