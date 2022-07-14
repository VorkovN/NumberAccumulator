#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H

#include <memory>

#include <Interfaces/ITransport.h>

#include "ClientSettings.h"

namespace apps::client
{

    class ClientFacade
    {
    public:
        explicit ClientFacade(ClientSettings&& settings);
        void start();

    private:
        std::unique_ptr<interface::ITransport> transport;
    };

}


#endif
