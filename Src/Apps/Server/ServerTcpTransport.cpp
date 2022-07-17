#include "ServerTcpTransport.h"

#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

namespace apps::server
{
    ServerTcpTransport::ServerTcpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {
        int _serverSocketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

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

        epoll_event event;
        event.data.fd = _serverSocketFd;
        event.events = EPOLLIN;

        epoll_ctl(epoll, EPOLL_CTL_ADD, _serverSocketFd, &event);

        while (!_sigIntReceived)
        {
            epoll_event events[255]; //todo убрать волшебное число
            int n = epoll_wait(epoll, events, 255, -1);
            for(uint32_t i = 0; i < n; ++i)
            {
                if (events[i].data.fd == _serverSocketFd)
                {
                    int peerSocket = accept(_serverSocketFd, nullptr, nullptr);
                    epoll_ctl(epoll, EPOLL_CTL_ADD, peerSocket, &events[i]);
                }
                else
                {
                    char buffer[1024];
                    ssize_t bytesReceived = recv(events[i].data.fd, buffer, 1024, MSG_NOSIGNAL);
                    if (bytesReceived == 0 && errno != EAGAIN)//todo что за ворое условие
                    {
                        shutdown(events[i].data.fd, SHUT_RDWR);
                        close(events[i].data.fd);
                    }
                    else if (bytesReceived > 0)
                    {
                        std::cout << "bytesReceived: " << bytesReceived << std::endl;
                        send(buffer, events[i].data.fd);
                    }
                }
            }
        }
    }

    void ServerTcpTransport::send(const std::string &data, int peerSocketFd)
    {
        std::string str = "12345";
        ::send(peerSocketFd, str.data(), str.size(), MSG_NOSIGNAL); //чтобы не прилетал SIG_PIPE //todo почему ::

    }

}