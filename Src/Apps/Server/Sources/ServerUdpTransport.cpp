#include "ServerUdpTransport.h"

#include <array>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "Constants.h"

namespace apps::server
{
    ServerUdpTransport::ServerUdpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {

    }

    void ServerUdpTransport::init()
    {
        if (_serverSocketFd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); _serverSocketFd == -1)
            throw std::logic_error("ServerUdpTransport: socket error");

        int optVal = 1;
        if(setsockopt(_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) == -1)
            throw std::logic_error("ServerTcpTransport: setsockopt error");

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            throw std::logic_error("ServerUdpTransport: bind error");
    }

    ServerUdpTransport::~ServerUdpTransport()
    {
        std::cout << "~ServerUdpTransport()" << std::endl;
    }

    std::optional<std::vector<IServerTransport::MiddleLayerData>> ServerUdpTransport::receive()
    {
        sockaddr peerSocketAddress{};
        socklen_t peerSocketAddressSize = sizeof(sockaddr);
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        ssize_t bytesReceived = recvfrom(_serverSocketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL, &peerSocketAddress, &peerSocketAddressSize);
        if (bytesReceived == -1)
            std::cout << "ServerUdpTransport: recvfrom exception" << std::endl;

        // ради красивого интерфейса и удобства обработки результатов пришлось пожертвовать адекватностью возвращаемого значения
        // в рамках данной архитектуры приложения не вижу других вариантов реализации этого return без вектора(точнее вижу, но они мне не нравятся еще больше)
        return std::vector<IServerTransport::MiddleLayerData>{{{buffer[0], buffer[1], buffer[2], buffer[3]}, buffer.data() + sizeof(uint32_t), peerSocketAddress}};
    }

    bool ServerUdpTransport::send(MiddleLayerData middleLayerData)
    {
        sockaddr peerSocketAddress = std::any_cast<sockaddr>(middleLayerData.peerInformation);
        std::array<char, OUTPUT_BUFFER_SIZE> buffer{};
        memcpy(buffer.data(), &middleLayerData.counterArray, COUNTER_SIZE);
        memcpy(buffer.data()+COUNTER_SIZE, middleLayerData.sendData.data(), middleLayerData.sendData.size());
        ssize_t bytesSent = sendto(_serverSocketFd, buffer.data(), middleLayerData.sendData.size()+OUTPUT_BUFFER_SIZE, MSG_NOSIGNAL, &peerSocketAddress, sizeof(peerSocketAddress));
        if (bytesSent == -1)
            return false;

        return true;
    }

}