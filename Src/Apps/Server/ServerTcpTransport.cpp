#include "ServerTcpTransport.h"

namespace apps::server
{
    ServerTcpTransport::ServerTcpTransport(std::string&& selfIp, uint32_t selfPort): _selfIp(std::move(selfIp)), _selfPort(selfPort) {}

    void ServerTcpTransport::init()
    {

    }

    void ServerTcpTransport::receive(const std::string &sendData)
    {

    }

    void ServerTcpTransport::send(const std::string &data)
    {

    }

}