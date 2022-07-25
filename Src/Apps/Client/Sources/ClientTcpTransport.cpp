#include "ClientTcpTransport.h"

#include <array>
#include <cstring>
#include <iostream>

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

        timeval receiveTimeout{.tv_sec=RECV_TIMEOUT, .tv_usec=0};
        if(setsockopt(_socketFd, SOL_SOCKET, SO_RCVTIMEO, &receiveTimeout, sizeof(receiveTimeout)) == -1)
            throw std::logic_error("ClientTcpTransport: setsockopt error");

        if (connect(_socketFd, (struct sockaddr *)&_socketAddress, _socketAddressSize) == -1)
            throw std::logic_error("ClientTcpTransport: connect error");

    }

    ClientTcpTransport::~ClientTcpTransport()
    {
        shutdown(_socketFd, SHUT_RDWR);
        std::cout << "~ClientTcpTransport()" << std::endl;
    }

    std::optional<std::string> ClientTcpTransport::receive()
    {
        std::array<char, INPUT_BUFFER_SIZE> buffer{};

        ssize_t bytesReceived;

        while (true)
        {
            bytesReceived = recv(_socketFd, buffer.data(), buffer.size(), MSG_NOSIGNAL);
            if (bytesReceived == -1)
                throw std::logic_error("ClientUdpTransport: recvfrom error. Timeout was ended");

            if (bytesReceived == 0)
                return {};

            if (bytesReceived < COUNTER_SIZE)
                throw std::logic_error("ClientUdpTransport: recvfrom error. Package size error");

            if (buffer[0] == _packageCounter.counterArray[0] &&
                buffer[1] == _packageCounter.counterArray[1] &&
                buffer[2] == _packageCounter.counterArray[2] &&
                buffer[3] == _packageCounter.counterArray[3] )
                break;
        }

        ++_packageCounter.counterNumber;
        return std::string(buffer.begin(), buffer.begin()+bytesReceived);
    }

    bool ClientTcpTransport::send(const std::string& sendData)
    {
        std::array<char, OUTPUT_BUFFER_SIZE> buffer{};
        memcpy(buffer.data(), &_packageCounter.counterArray, COUNTER_SIZE);
        memcpy(buffer.data()+COUNTER_SIZE, sendData.data(), sendData.size());
        ssize_t bytesSent = ::send(_socketFd, buffer.data(), sendData.size()+COUNTER_SIZE, MSG_NOSIGNAL);
        if (bytesSent == -1)
            return false;

        return true;
    }

}