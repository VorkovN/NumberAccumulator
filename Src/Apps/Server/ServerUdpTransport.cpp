#include "ServerUdpTransport.h"

#include <stdexcept>
#include <exception>
#include <iostream>
#include <array>

#include "Constants.h"

namespace apps::server
{
    ServerUdpTransport::ServerUdpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {

    }

    void ServerUdpTransport::init()
    {
        if (_serverSocketFd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); _serverSocketFd == -1)
            throw std::logic_error("ServerUdpTransport: socket failed");

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            throw std::logic_error("ServerUdpTransport: bind failed");
    }

    ServerUdpTransport::~ServerUdpTransport()
    {
        std::cout << "~ServerUdpTransport()" << std::endl;
    }

    std::optional<ServerTransport::MiddleLayerData> ServerUdpTransport::receive()
    {
        sockaddr peerSocketAddress{};
        socklen_t peerSocketAddressSize = sizeof(sockaddr);
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        int bytesReceived = recvfrom(_serverSocketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL, &peerSocketAddress, &peerSocketAddressSize);
        if (bytesReceived == -1)
            return {};

        return MiddleLayerData{buffer.data(), peerSocketAddress};
    }


    void ServerUdpTransport::send(MiddleLayerData middleLayerData)
    {
        sockaddr peerSocketAddress = std::any_cast<sockaddr>(middleLayerData.peerInformation);
        int bytesSent = sendto(_serverSocketFd, middleLayerData.sendData.data(), middleLayerData.sendData.size(), MSG_NOSIGNAL, &peerSocketAddress, sizeof(peerSocketAddress));
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}