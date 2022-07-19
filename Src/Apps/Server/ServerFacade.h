#ifndef NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H
#define NUMBERACCUMULATOR_APPS_SERVER_SERVERFACADE_H

#include <memory>
#include <set>

#include "ServerSettings.h"
#include "IServerTransport.h"

namespace apps::server
{

    class ServerFacade
    {
    public:
        explicit ServerFacade(ServerSettings&& settings);
        void start();

    private:
        void handleReceivedConnection(IServerTransport* transport);
        std::string countNumbersInString(std::string_view inputString);
        std::string makeAnswerString(std::multiset<int>&& nums, int sum);

    public:
        static bool _needToKillProgram;

    private:
        std::unique_ptr<IServerTransport> _udpTransport;
        std::unique_ptr<IServerTransport> _tcpTransport;

    };

}

#endif
