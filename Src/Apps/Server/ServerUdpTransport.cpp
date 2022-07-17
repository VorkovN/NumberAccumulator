#include "ServerUdpTransport.h"

#include <iostream>


namespace apps::server
{
    ServerUdpTransport::ServerUdpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {
        _serverSocketFd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            exit(0);
    }

    ServerUdpTransport::~ServerUdpTransport()
    {
        std::cout << "~ServerUdpTransport()" << std::endl;
    }

    void ServerUdpTransport::receive()
    {
        sockaddr_in peerSocketAddress{};
        socklen_t peerSocketAddressSize = sizeof(sockaddr_in);
        const ssize_t bufferSize = 1024; //todo нужно ли сделать больше
        char buffer[bufferSize];
        //todo можно ли в один поток с хендлером?
        while (!_sigIntReceived)
        {
            int bytesReceived = recvfrom(_serverSocketFd, buffer, 1024, MSG_NOSIGNAL, (sockaddr*)&peerSocketAddress, &peerSocketAddressSize);
            if (bytesReceived == -1)
                continue; //TODO сделать обработку ошибок
            std::cout << "bytesReceived: " << bytesReceived << std::endl;
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
        ssize_t bytesSent = sendto(_serverSocketFd, data.data(), data.size(), MSG_NOSIGNAL, (sockaddr*)&peerSocketAddress, sizeof(peerSocketAddress));
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}