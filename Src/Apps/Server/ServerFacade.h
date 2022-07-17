#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H

#include <memory>

//#include <Interfaces/ITransport.h>

#include "ServerSettings.h"
#include "ServerTransport.h"

namespace apps::server
{

    class ServerFacade
    {
    public:
        explicit ServerFacade(ServerSettings&& settings);
        void start();

    private:
        std::unique_ptr<ServerTransport> _udpTransport;
        std::unique_ptr<ServerTransport> _tcpTransport;

    };

}

#endif
