#include "ClientTcpTransport.h"

#include <utility>

namespace apps::client
{
    ClientTcpTransport::ClientTcpTransport(std::string&& serverIp, uint32_t serverPort):_serverIp(std::move(serverIp)), _serverPort(serverPort) {}

    void ClientTcpTransport::init()
    {

    }

    void ClientTcpTransport::receive(const std::string &sendData)
    {

    }

    void ClientTcpTransport::send(const std::string &data)
    {

    }

}