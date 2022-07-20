#include "ClientTransport.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>


namespace apps::client
{

    ClientTransport::ClientTransport(std::string &&serverIp, uint32_t serverPort): _serverIp(std::move(serverIp)), _serverPort(serverPort)
    {
        bzero(&_socketAddress, sizeof(_socketAddress));
        _socketAddress.sin_port = htons(_serverPort);
        _socketAddress.sin_family = AF_INET;
        _socketAddress.sin_addr.s_addr = inet_addr(_serverIp.data());
        _socketAddressSize = sizeof(sockaddr_in);
    }

    ClientTransport::~ClientTransport()
    {
        std::cout << "~ClientTransport()" << std::endl;
        close(_socketFd);
    }

}
