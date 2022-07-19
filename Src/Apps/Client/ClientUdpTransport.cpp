#include <iostream>
#include <unistd.h>
#include <array>
#include "ClientUdpTransport.h"

#include "Constants.h"

namespace apps::client
{
    ClientUdpTransport::ClientUdpTransport(std::string&& serverIp, uint32_t serverPort): ClientTransport(std::move(serverIp), serverPort)
    {

    }

    void ClientUdpTransport::init()
    {
        if (_socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); _socketFd == -1)
            throw std::logic_error("ClientUdpTransport: socket error");
    }

    ClientUdpTransport::~ClientUdpTransport()
    {
        std::cout << "~ClientUdpTransport()" << std::endl;
    }

    std::optional<std::string> ClientUdpTransport::receive()
    {
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        ssize_t bytesReceived = recvfrom(_socketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL, nullptr, nullptr);
        if (bytesReceived == -1)
            return {};

        return buffer.data();
    }

    bool ClientUdpTransport::send(const std::string& sendData)
    {
        ssize_t bytesSent = sendto(_socketFd, sendData.data(), sendData.size(), MSG_NOSIGNAL,(struct sockaddr*)&_socketAddress, _socketAddressSize);
        if (bytesSent == -1)
            return false;

        return true;
    }

}