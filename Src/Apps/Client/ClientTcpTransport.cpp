#include "ClientTcpTransport.h"

#include <iostream>
#include <utility>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

namespace apps::client
{
    ClientTcpTransport::ClientTcpTransport(std::string&& serverIp, uint32_t serverPort): ClientTransport(std::move(serverIp), serverPort)
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
        const size_t bufferSize = 1024; //todo нужно ли сделать больше
        char buffer[bufferSize];

        recv(_socketFd, buffer, 1024, MSG_NOSIGNAL);
//        if (recv(_socketFd, buffer, 1024, MSG_NOSIGNAL));
//            exit(0); //TODO сделать обработку ошибок

    }

    void ClientTcpTransport::send(const std::string &data)
    {
        std::string str = "123";
        ::send(_socketFd, str.data(), str.size(), MSG_NOSIGNAL); //чтобы не прилетал SIG_PIPE //todo почему ::

    }

}