#include <iostream>
#include <unistd.h>
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
            throw std::logic_error("ClientUdpTransport: socket failed");

    }

    ClientUdpTransport::~ClientUdpTransport()
    {
        std::cout << "~ClientUdpTransport()" << std::endl;
    }

    std::optional<std::string> ClientUdpTransport::receive()
    {
        char buffer[INPUT_BUFFER_SIZE];

        int bytesReceived = recvfrom(_socketFd, (void*)buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (bytesReceived < 0)
            return {};

        return buffer;


    }

    void ClientUdpTransport::send(const std::string& sendData)
    {
        int bytesSent = sendto(_socketFd, sendData.data(), sendData.size(), MSG_NOSIGNAL,(struct sockaddr*)&_socketAddress, _socketAddressSize);
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}