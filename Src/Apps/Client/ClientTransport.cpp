#include "ClientTransport.h"

#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <unistd.h>


namespace apps::client
{

    ClientTransport::ClientTransport(std::string &&serverIp, uint32_t serverPort): _serverIp(std::move(serverIp)), _serverPort(serverPort)
    {
        bzero(&_socketAddress, sizeof(_socketAddress));
        _socketAddress.sin_port = htons(_serverPort);
        if (inet_pton(AF_INET, _serverIp.data(), &_socketAddress.sin_addr))
            exit(0);

        _socketAddressSize = sizeof(_socketAddress);
    }

    ClientTransport::~ClientTransport()
    {
        std::cout << "~ClientTransport()" << std::endl;
        close(_socketFd);
    }

    void ClientTransport::handleInput()
    {
        while (!_sigIntReceived)
            sleep(1);
    }

    void ClientTransport::init()
    {
        std::thread(&ITransport::receive, this).detach();
        handleInput();
    }
}
