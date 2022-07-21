#ifndef NUMBERACCUMULATOR_APPS_CLIENT_CONSTANTS_H
#define NUMBERACCUMULATOR_APPS_CLIENT_CONSTANTS_H

#include <cinttypes>

namespace apps::client
{
    static constexpr uint32_t COUNTER_SIZE = 4;
    static constexpr uint32_t RECV_TIMEOUT = 5;
    static constexpr uint32_t INPUT_BUFFER_SIZE = 1024;
    static constexpr uint32_t OUTPUT_BUFFER_SIZE = 1024;

}

#endif