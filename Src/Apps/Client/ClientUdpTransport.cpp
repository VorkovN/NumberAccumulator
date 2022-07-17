#include <iostream>
#include "ClientUdpTransport.h"



namespace apps::client
{
    ClientUdpTransport::ClientUdpTransport(std::string&& serverIp, uint32_t serverPort): ClientTransport(std::move(serverIp), serverPort)
    {
        _socketFd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_socketFd == -1)
            exit(0); //TODO сделать обработку ошибок
    }

    ClientUdpTransport::~ClientUdpTransport()
    {
        std::cout << "~ClientUdpTransport()" << std::endl;
    }

    void ClientUdpTransport::receive()
    {
        const ssize_t bufferSize = 1024; //todo нужно ли сделать больше
        char buffer[bufferSize];
        //todo можно ли в один поток с хендлером?
        while (!_sigIntReceived)
        {
            ssize_t bytesReceived = recvfrom(_socketFd, (void*)buffer, sizeof(buffer), 0, (struct sockaddr*)&_socketAddress, &_socketAddressSize);
            if (bytesReceived < 0)
                return; //TODO сделать обработку ошибок

            std::cout << buffer << std::endl; //todo вынести в отдельный метод
        }
    }

    void ClientUdpTransport::send(const std::string &data)
    {
        ssize_t bytesSent = sendto(_socketFd, data.data(), data.size(), MSG_NOSIGNAL,(struct sockaddr*)&_socketAddress, _socketAddressSize);
        if (bytesSent < 0)
            return; //TODO сделать обработку ошибок
    }

}