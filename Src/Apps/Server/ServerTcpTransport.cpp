#include "ServerTcpTransport.h"

#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <map>

#include "Constants.h"

namespace apps::server
{
    ServerTcpTransport::ServerTcpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {
        _serverSocketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            exit(0);

        listen(_serverSocketFd, SOMAXCONN);

        epoll = epoll_create1(0);

        epoll_event event{};
        event.data.fd = _serverSocketFd;
        event.events = EPOLLIN;
        events[event.data.fd] = event;

        epoll_ctl(epoll, EPOLL_CTL_ADD, _serverSocketFd, &events[event.data.fd]);
    }

    ServerTcpTransport::~ServerTcpTransport()
    {
        std::cout << "~ServerTcpTransport()" << std::endl;
    }

    std::optional<ServerTransport::MiddleLayerData> ServerTcpTransport::receive()
    {
        epoll_event activeEvents[MAX_EPOLL_EVENTS];
        int n = epoll_wait(epoll, activeEvents, MAX_EPOLL_EVENTS, -1);
        for(uint32_t i = 0; i < n; ++i)
        {
            epoll_event event{};

            if (activeEvents[i].data.fd == _serverSocketFd)
            {
                int peerSocket = accept(_serverSocketFd, nullptr, nullptr);

                event.data.fd = peerSocket;
                event.events = EPOLLIN;
                events[event.data.fd] = event;

                epoll_ctl(epoll, EPOLL_CTL_ADD, peerSocket, &events[event.data.fd]);
            }
            else
            {
                std::array<char, INPUT_BUFFER_SIZE> buffer{};;
                ssize_t bytesReceived = recv(activeEvents[i].data.fd, buffer.data(), buffer.size(), MSG_NOSIGNAL);
                if (bytesReceived == 0 && errno != EAGAIN)
                {
                    shutdown(activeEvents[i].data.fd, SHUT_RDWR);
                    close(activeEvents[i].data.fd);
                    events.erase(event.data.fd);
                }
                else if (bytesReceived > 0)
                {
                    int kostyl = activeEvents[i].data.fd;
                    return ServerTransport::MiddleLayerData{buffer.data(), kostyl};
                }
            }
        }
        return {};
    }

    void ServerTcpTransport::send(MiddleLayerData middleLayerData)
    {
        int peerSocketFd = std::any_cast<int>(middleLayerData.peerInformation);
        int bytesSent = ::send(peerSocketFd, middleLayerData.sendData.data(), middleLayerData.sendData.size(), MSG_NOSIGNAL);
        if (bytesSent < 0)
            return;
    }

}