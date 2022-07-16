#include "ClientTcpTransport.h"

#include <iostream>
#include <utility>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

namespace apps::client
{
    ClientTcpTransport::ClientTcpTransport(std::string&& serverIp, uint32_t serverPort):_serverIp(std::move(serverIp)), _serverPort(serverPort)
    {
        _socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_socketFd == -1)
            exit(0);

        if (connect(_socketFd, (struct sockaddr *)&_socketAddress, sizeof _socketAddress) == -1)
            exit(0);
    }

    ClientTcpTransport::~ClientTcpTransport()
    {
        std::cout << "~ClientTcpTransport()" << std::endl;
    }

    void ClientTcpTransport::receive()
    {

    }

    void ClientTcpTransport::send(const std::string &data)
    {

    }

}