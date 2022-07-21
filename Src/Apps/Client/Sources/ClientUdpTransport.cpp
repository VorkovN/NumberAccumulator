#include "ClientUdpTransport.h"

#include <array>
#include <cstring>
#include <iostream>

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

        timeval receiveTimeout{.tv_sec=RECV_TIMEOUT, .tv_usec=0};
        if(setsockopt(_socketFd, SOL_SOCKET, SO_RCVTIMEO, &receiveTimeout, sizeof(receiveTimeout)) == -1)
            throw std::logic_error("ClientUdpTransport: setsockopt error");

    }

    ClientUdpTransport::~ClientUdpTransport()
    {
        std::cout << "~ClientUdpTransport()" << std::endl;
    }

    std::optional<std::string> ClientUdpTransport::receive()
    {
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        while (true)
        {
            ssize_t bytesReceived = recvfrom(_socketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL, nullptr, nullptr);
            if (bytesReceived == -1)
                return {};

            if (buffer[0] == _packageCounter.counterArray[0] &&
                buffer[1] == _packageCounter.counterArray[1] &&
                buffer[2] == _packageCounter.counterArray[2] &&
                buffer[3] == _packageCounter.counterArray[3] )
                break;
        }

        if (++_packageCounter.counterNumber == 0) ++_packageCounter.counterNumber;
        return buffer.data()+sizeof(_packageCounter);
    }

    bool ClientUdpTransport::send(const std::string& sendData)
    {
        std::array<char, OUTPUT_BUFFER_SIZE> buffer{};
        memcpy(buffer.data(), &_packageCounter.counterArray, COUNTER_SIZE);
        memcpy(buffer.data()+COUNTER_SIZE, sendData.data(), sendData.size());
        ssize_t bytesSent = sendto(_socketFd, buffer.data(), sendData.size()+COUNTER_SIZE, MSG_NOSIGNAL,(struct sockaddr*)&_socketAddress, _socketAddressSize);
        if (bytesSent == -1)
            return false;

        return true;
    }

}