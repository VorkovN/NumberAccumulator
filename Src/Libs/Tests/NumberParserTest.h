#ifndef NUMBERACCUMULATOR_APPS_TESTS_SOMELIBTEST_H
#define NUMBERACCUMULATOR_APPS_TESTS_SOMELIBTEST_H

#include "NumberParser.h"

namespace tests::libs
{

    TEST(getNumbersFromStringTest, simpleTest)
    {
        std::string testString = "1 2 3";
        std::multiset<int> referenceSet = {1, 2, 3};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, minusNumbersTest)
    {
        std::string testString = "-4 5 -6 -9";
        std::multiset<int> referenceSet = {-4, 5, -6, -9};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, withWordsTest)
    {
        std::string testString = "20 apples, 30 bananas, 15 peaches and 1 watermelon";
        std::multiset<int> referenceSet = {20, 30, 15, 1};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, emptyTest)
    {
        std::string testString = "apples, bananas, peaches and -watermelon";
        std::multiset<int> referenceSet = {};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, oneSimbolTest)
    {
        std::string testString = "7";
        std::multiset<int> referenceSet = {7};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

    TEST(getNumbersFromStringTest, doubleSimbolTest)
    {
        std::string testString = "7 7 7";
        std::multiset<int> referenceSet = {7, 7, 7};
        std::multiset<int> resultSet = ::libs::NumbersParser::getNumbersFromString(testString);
        ASSERT_EQ(resultSet, referenceSet );
    }

}
#endif
