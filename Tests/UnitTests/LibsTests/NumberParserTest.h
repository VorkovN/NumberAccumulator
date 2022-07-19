#ifndef NUMBERACCUMULATOR_APPS_TESTS_SOMELIBTEST_H
#define NUMBERACCUMULATOR_APPS_TESTS_SOMELIBTEST_H

#include <Libs/NumberParser.h>

namespace tests::libs
{

    TEST(getNumbersFromStringTest, simpleTest)
    {
        std::string testString = "1 2 3";
        std::set<int> referenceSet = {1, 2, 3};
        std::set<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, minusNumbersTest)
    {
        std::string testString = "-4 5 -6 -9";
        std::set<int> referenceSet = {-4, 5, -6, -9};
        std::set<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, withWordsTest)
    {
        std::string testString = "20 apples, 30 bananas, 15 peaches and 1 watermelon";
        std::set<int> referenceSet = {20, 30, 15, 1};
        std::set<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, emptyTest)
    {
        std::string testString = "apples, bananas, peaches and -watermelon";
        std::set<int> referenceSet = {};
        std::set<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

}
#endif
