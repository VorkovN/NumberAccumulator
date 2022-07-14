#include "ClientUdpTransport.h"

#include <utility>

namespace apps::client
{
    ClientUdpTransport::ClientUdpTransport(std::string&& serverIp, uint32_t serverPort): _serverIp(std::move(serverIp)), _serverPort(serverPort) {}

    void ClientUdpTransport::init()
    {

    }

    void ClientUdpTransport::receive(const std::string &sendData)
    {

    }

    void ClientUdpTransport::send(const std::string &data)
    {

    }

}