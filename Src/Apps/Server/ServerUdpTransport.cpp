#include "ServerUdpTransport.h"

#include <iostream>
#include <utility>

namespace apps::server
{
    ServerUdpTransport::ServerUdpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort) {}

    ServerUdpTransport::~ServerUdpTransport()
    {
        std::cout << "~ServerUdpTransport()" << std::endl;
    }

    void ServerUdpTransport::receive()
    {
        sockaddr_in peerSocketAddress{};
        const ssize_t bufferSize = 1024; //todo нужно ли сделать больше
        char buffer[bufferSize];
        //todo можно ли в один поток с хендлером?
        while (!_sigIntReceived)
        {
            ssize_t bytesReceived = recvfrom(_serverSocketFd, (void*)buffer, sizeof(buffer), MSG_NOSIGNAL, (struct sockaddr*)&peerSocketAddress, nullptr);
            if (bytesReceived < 0)
                return; //TODO сделать обработку ошибок

            std::cout << buffer << std::endl; //todo вынести в отдельный метод
            std::string testStr = "qwerty";
            send(testStr, std::move(peerSocketAddress)); //todo прочем можно и убрать move
        }
    }


//    void ServerUdpTransport::send(const std::string &data)
//    {
//
//    }

    void ServerUdpTransport::send(const std::string &data, sockaddr_in&& peerSocketAddress)
    {
        ssize_t bytesSent = sendto(_serverSocketFd, data.data(), data.size(), MSG_NOSIGNAL,(struct sockaddr*)&peerSocketAddress, sizeof(peerSocketAddress));
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}