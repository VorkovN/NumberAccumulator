#include "ServerTransport.h"

#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>


namespace apps::server
{
    ServerTransport::ServerTransport(std::string &&serverIp, uint32_t serverPort): _serverIp(std::move(serverIp)), _serverPort(serverPort)
    {
        bzero(&_serverSocketAddress, sizeof(_serverSocketAddress));
        _serverSocketAddress.sin_port = htons(_serverPort);
        _serverSocketAddress.sin_family = AF_INET;
        _serverSocketAddress.sin_addr.s_addr = inet_addr(_serverIp.data());
        _serverSocketAddressSize = sizeof(_serverSocketAddress);
    }

    ServerTransport::~ServerTransport()
    {
        std::cout << "~ServerTransport()" << std::endl;
        close(_serverSocketFd);
    }

}
