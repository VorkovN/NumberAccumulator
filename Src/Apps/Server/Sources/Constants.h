#ifndef NUMBERACCUMULATOR_APPS_SERVER_CONSTANTS_H
#define NUMBERACCUMULATOR_APPS_SERVER_CONSTANTS_H

#include <cinttypes>

namespace apps::server
{
    static constexpr uint32_t INPUT_BUFFER_SIZE = 1024;
    static constexpr uint32_t MAX_EPOLL_EVENTS = 1024;

}

#endif