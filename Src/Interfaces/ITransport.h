#ifndef NUMBERACCUMULATOR_INTERFACE_ITRANSPORT_H
#define NUMBERACCUMULATOR_INTERFACE_ITRANSPORT_H

#include <string>

namespace interface
{
    class ITransport
    {
    public:
        virtual void start() = 0;
        virtual void receive() = 0;
//        virtual void send(const std::string& data) = 0; // серверу нужен еще адрес клиента передавать в аргументах
    };
}

#endif
