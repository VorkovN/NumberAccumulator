#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CLIENTFACADE_H

#include <memory>

//#include <Interfaces/ITransport.h>

#include "ClientSettings.h"
#include "ClientTransport.h"

namespace apps::client
{

    class ClientFacade
    {
    public:
        explicit ClientFacade(ClientSettings&& settings);
        void start();

    private:
        void handleInput();
        void handleReceive();
        void printServerAnswer(const std::string& serverAnswer);
    public:
        static bool _sigIntReceived;

    private:
        std::unique_ptr<ClientTransport> _transport;
    };

}


#endif
