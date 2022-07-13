#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H

#include "ClientSettings.h"

namespace apps::client
{

    class ClientFacade
    {
    public:
        explicit ClientFacade(ClientSettings&& settings);
        void start();
    private:

    };

}


#endif
