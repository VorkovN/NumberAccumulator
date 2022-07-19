#include "ClientTcpTransport.h"

#include <iostream>
#include <utility>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#include "Constants.h"

namespace apps::client
{
    ClientTcpTransport::ClientTcpTransport(std::string&& serverIp, uint32_t serverPort): ClientTransport(std::move(serverIp), serverPort)
    {

    }

    void ClientTcpTransport::init()
    {
        if (_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); _socketFd == -1)
            throw std::logic_error("ClientTcpTransport: socket failed");


        if (connect(_socketFd, (struct sockaddr *)&_socketAddress, _socketAddressSize) == -1)
            throw std::logic_error("ClientTcpTransport: connect failed");

    }

    ClientTcpTransport::~ClientTcpTransport()
    {
        std::cout << "~ClientTcpTransport()" << std::endl;
    }

    std::optional<std::string> ClientTcpTransport::receive()
    {
        char buffer[INPUT_BUFFER_SIZE];

        int bytesReceived = recv(_socketFd, buffer, INPUT_BUFFER_SIZE, MSG_NOSIGNAL);
        if (bytesReceived < 0)
            return {};

        return buffer;
    }

    void ClientTcpTransport::send(const std::string& sendData)
    {
        int bytesSent = ::send(_socketFd, sendData.data(), sendData.size(), MSG_NOSIGNAL); //чтобы не прилетал SIG_PIPE //todo почему ::
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}