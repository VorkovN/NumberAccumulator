#ifndef NUMBERACCUMULATOR_LIBS_NUMBERPARSER_H
#define NUMBERACCUMULATOR_LIBS_NUMBERPARSER_H

#include <optional>
#include <string_view>
#include <unistd.h>

namespace libs
{
class NumbersParser
{
public:
    static std::multiset<int> getNumbersFromString(std::string_view inputString)
    {
        if (inputString.empty())
            return {};

        if (inputString.size() == 1 && inputString.front() >= '0' && inputString.front() <= '9')
            return {atoi(&inputString.front())};

        std::multiset<int> foundNumbers;

        auto iteratorFirst = inputString.begin();
        auto iteratorLast = inputString.begin()+1;
        while (iteratorFirst != inputString.end())
        {
            bool isFirstIteratorOnDigit = *iteratorFirst >= '0' && *iteratorFirst <= '9';
            bool isLastIteratorOnDigit = *iteratorLast >= '0' && *iteratorLast <= '9';
            bool isLastNumber = iteratorLast == inputString.end() - 1;
            if (isFirstIteratorOnDigit)
            {
                if ((!isLastIteratorOnDigit || isLastNumber) && iteratorFirst <= iteratorLast)
                {
                    int parsedNumber = atoi(std::string_view {iteratorFirst, static_cast<uint32_t>(std::distance(iteratorFirst, iteratorLast)) - 1}.data());
                    if (iteratorFirst != inputString.begin() && *(iteratorFirst-1) == '-') parsedNumber *= -1; // проверка на отрицательность числа
                    foundNumbers.insert(parsedNumber);
                    iteratorFirst = iteratorLast+1;
                    continue;
                }
                ++iteratorLast;
                continue;
            }
            ++iteratorFirst;
        }

        return foundNumbers;
    }

};

}

#endif
