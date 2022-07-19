#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H

#include <memory>
#include <set>

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
        void handleReceivedConnection(ServerTransport* transport);
        std::string countNumbersInString(std::string_view inputString);
        std::string makeAnswerString(std::set<int>&& nums, int sum);

    public:
        static bool _needToKillProgram;

    private:
        std::shared_ptr<ServerTransport> _udpTransport;
        std::shared_ptr<ServerTransport> _tcpTransport;

    };

}

#endif
