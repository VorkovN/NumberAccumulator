#include "ClientTcpTransport.h"

#include <iostream>
#include <utility>
#include <arpa/inet.h>
#include <array>

#include "Constants.h"

namespace apps::client
{
    ClientTcpTransport::ClientTcpTransport(std::string&& serverIp, uint32_t serverPort): ClientTransport(std::move(serverIp), serverPort)
    {

    }

    void ClientTcpTransport::init()
    {
        if (_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); _socketFd == -1)
            throw std::logic_error("ClientTcpTransport: socket error");


        if (connect(_socketFd, (struct sockaddr *)&_socketAddress, _socketAddressSize) == -1)
            throw std::logic_error("ClientTcpTransport: connect error");

    }

    ClientTcpTransport::~ClientTcpTransport()
    {
        std::cout << "~ClientTcpTransport()" << std::endl;
    }

    std::optional<std::string> ClientTcpTransport::receive()
    {
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        ssize_t bytesReceived = recv(_socketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL);
        if (bytesReceived == -1)
            return {};

        return buffer.data();
    }

    bool ClientTcpTransport::send(const std::string& sendData)
    {
        ssize_t bytesSent = ::send(_socketFd, sendData.data(), sendData.size(), MSG_NOSIGNAL);
        if (bytesSent == -1)
            return false;

        return true;
    }

}