#include "ServerTransport.h"

#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <unistd.h>


namespace apps::server
{
    bool ServerTransport::_sigIntReceived = false;

    ServerTransport::ServerTransport(std::string &&serverIp, uint32_t serverPort): _serverIp(std::move(serverIp)), _serverPort(serverPort)
    {
        bzero(&_serverSocketAddress, sizeof(_serverSocketAddress));
        _serverSocketAddress.sin_port = htons(_serverPort);
        _serverSocketAddress.sin_family = AF_INET; //todo зачем его присваивать 2 раза?
        if (inet_pton(AF_INET, _serverIp.data(), &_serverSocketAddress.sin_addr))
            exit(0);

        _serverSocketAddressSize = sizeof(_serverSocketAddress);

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize))
            exit(0);
    }

    ServerTransport::~ServerTransport()
    {
        std::cout << "~ServerTransport()" << std::endl;
        close(_serverSocketFd);
    }


    void ServerTransport::start()
    {
        receive();
    }
}
