#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H

#include <memory>

#include "ClientSettings.h"
#include "IClientTransport.h"

namespace apps::client
{

    class ClientFacade
    {
    public:
        explicit ClientFacade(ClientSettings&& settings);
        void start();

    private:
        void handleInput();
        void printServerAnswer(const std::string& serverAnswer);

    public:
        static bool _needToKillProgram;

    private:
        std::unique_ptr<IClientTransport> _transport;
    };

}


#endif
