#include "ServerTcpTransport.h"

#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <map>

namespace apps::server
{
    ServerTcpTransport::ServerTcpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {
        _serverSocketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            exit(0);
    }

    ServerTcpTransport::~ServerTcpTransport()
    {
        std::cout << "~ServerTcpTransport()" << std::endl;
    }

    void ServerTcpTransport::receive()
    {

        listen(_serverSocketFd, SOMAXCONN);

        int epoll = epoll_create1(0);//todo нужно ли использовать epoll_create()

        std::map<int, epoll_event> events;//todo наверно нужно создать, чтобы на перетерлись в памяти ивенты
        epoll_event event{};
        event.data.fd = _serverSocketFd;
        event.events = EPOLLIN;
        events[event.data.fd] = event;

        int res = epoll_ctl(epoll, EPOLL_CTL_ADD, _serverSocketFd, &events[event.data.fd]);

        while (!_sigIntReceived)
        {
            epoll_event activeEvents[255]; //todo убрать волшебное число
            int n = epoll_wait(epoll, activeEvents, 255, -1);
            for(uint32_t i = 0; i < n; ++i)
            {
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
                    char buffer[1024];
                    ssize_t bytesReceived = recv(activeEvents[i].data.fd, buffer, 1024, MSG_NOSIGNAL);
                    if (bytesReceived == 0 && errno != EAGAIN)//todo что за второе условие
                    {
                        shutdown(activeEvents[i].data.fd, SHUT_RDWR);
                        close(activeEvents[i].data.fd);
                        events.erase(event.data.fd);
                    }
                    else if (bytesReceived > 0)
                    {
                        std::cout << "bytesReceived: " << bytesReceived << std::endl;
                        std::cout << "message: " << buffer << std::endl;
                        send(buffer, activeEvents[i].data.fd);
                    }
                }
            }
        }
    }

    void ServerTcpTransport::send(const std::string &data, int peerSocketFd)
    {
        ::send(peerSocketFd, data.data(), data.size(), MSG_NOSIGNAL); //чтобы не прилетал SIG_PIPE

    }

}