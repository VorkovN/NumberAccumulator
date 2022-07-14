#include "ServerUdpTransport.h"

#include <utility>

namespace apps::server
{
    ServerUdpTransport::ServerUdpTransport(std::string&& selfIp, uint32_t selfPort): _selfIp(std::move(selfIp)), _selfPort(selfPort) {}

    void ServerUdpTransport::init()
    {

    }

    void ServerUdpTransport::receive(const std::string &sendData)
    {

    }

    void ServerUdpTransport::send(const std::string &data)
    {

    }

}