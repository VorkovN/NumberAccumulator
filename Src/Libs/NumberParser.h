#ifndef NUMBERACCUMULATOR_LIBS_NUMBERPARSER_H
#define NUMBERACCUMULATOR_LIBS_NUMBERPARSER_H

#include <optional>
#include <string_view>
#include <unistd.h>

namespace libs
{
class NumbersParser
{
    static std::optional<int32_t> countNumbersInString(std::string_view inputString)
    {
        return {}; //TODO реализовать после уточнения формата входных данных
    }
};

}

#endif
