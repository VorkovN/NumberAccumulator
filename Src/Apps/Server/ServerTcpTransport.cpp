#include "ServerTcpTransport.h"

#include <iostream>
#include <unistd.h>

#include "Constants.h"

namespace apps::server
{
    ServerTcpTransport::ServerTcpTransport(std::string&& selfIp, uint32_t selfPort): ServerTransport(std::move(selfIp), selfPort)
    {

    }

    void ServerTcpTransport::init()
    {
        if (_serverSocketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ); _serverSocketFd == -1)
            throw std::logic_error("ServerTcpTransport: socket error");

        int optVal = 1;
        if(setsockopt(_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) == -1)
            throw std::logic_error("ServerTcpTransport: bind error");

        if(bind(_serverSocketFd, (sockaddr*)(&_serverSocketAddress), _serverSocketAddressSize) == -1)
            throw std::logic_error("ServerTcpTransport: bind error");

        if(listen(_serverSocketFd, SOMAXCONN) == -1)
            throw std::logic_error("ServerTcpTransport: listen error");

        if (_epoll = epoll_create1(0); _epoll == -1)
            throw std::logic_error("ServerTcpTransport: epoll_create1 error");

        epoll_event event{};
        event.data.fd = _serverSocketFd;
        event.events = EPOLLIN;
        _events[event.data.fd] = event;

        if (epoll_ctl(_epoll, EPOLL_CTL_ADD, _serverSocketFd, &_events[event.data.fd]) == -1)
            throw std::logic_error("ServerTcpTransport: epoll_ctl error");

    }

    ServerTcpTransport::~ServerTcpTransport()
    {
        std::cout << "~ServerTcpTransport()" << std::endl;
    }

    std::optional<std::vector<IServerTransport::MiddleLayerData>> ServerTcpTransport::receive()
    {
        epoll_event activeEvents[MAX_EPOLL_EVENTS];
        int activeEventsCount = epoll_wait(_epoll, activeEvents, MAX_EPOLL_EVENTS, -1);
        if (activeEventsCount == -1)
            return {};

        std::vector<IServerTransport::MiddleLayerData> tasks;
        tasks.reserve(activeEventsCount);

        for(uint32_t i = 0; i < activeEventsCount; ++i)
        {
            epoll_event event{};

            if (activeEvents[i].data.fd == _serverSocketFd) //при получении события на сервер сокет, добавляем новый сокет
            {
                int peerSocket = accept(_serverSocketFd, nullptr, nullptr);
                if (peerSocket == -1)
                {
                    std::cout << "ServerTcpTransport: accept exception";
                    continue;
                }

                event.data.fd = peerSocket;
                event.events = EPOLLIN;
                _events[event.data.fd] = event;

                int epollCtlResult = epoll_ctl(_epoll, EPOLL_CTL_ADD, peerSocket, &_events[event.data.fd]);
                if (epollCtlResult == -1)
                {
                    std::cout << "ServerTcpTransport: epoll_ctl exception";
                    continue;
                }
            }
            else //при получении события на обычный сокет, читаем из этого сокета
            {
                std::array<char, INPUT_BUFFER_SIZE> buffer{};;
                ssize_t bytesReceived = recv(activeEvents[i].data.fd, buffer.data(), buffer.size(), MSG_NOSIGNAL);

                if (bytesReceived == -1)
                {
                    std::cout << "ServerTcpTransport: epoll_ctl exception";
                    continue;
                }

                if (bytesReceived > 0)
                {
                    int kostyl = activeEvents[i].data.fd; //необходимо по причине, что невозможно передать в std::any упакованное поле
                    tasks.push_back({buffer.data(), kostyl});
                    continue;
                }

                if (bytesReceived == 0 && errno != EAGAIN) // если произошло событие на сокете, но данных для чтения в нем нет, значит сокет завершил соединение
                {
                    shutdown(activeEvents[i].data.fd, SHUT_RDWR);
                    close(activeEvents[i].data.fd);
                    _events.erase(event.data.fd);
                }

            }
        }
        return tasks;
    }

    bool ServerTcpTransport::send(MiddleLayerData middleLayerData)
    {
        int peerSocketFd = std::any_cast<int>(middleLayerData.peerInformation);

        ssize_t bytesSent = ::send(peerSocketFd, middleLayerData.sendData.data(), middleLayerData.sendData.size(), MSG_NOSIGNAL);
        if (bytesSent == -1)
            return false;

        return true;
    }

}