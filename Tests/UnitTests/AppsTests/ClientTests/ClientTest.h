#ifndef NUMBERACCUMULATOR_TESTS_SOMECLIENTTEST_H
#define NUMBERACCUMULATOR_TESTS_SOMECLIENTTEST_H

#include "ClientSettingsParser.h"

namespace tests
{

    TEST(ClientSettingsParserTest, printTest)
    {
        int argc = 2;
        std::array<char*, 2> argv{"testName", "-h"};
        auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(!settingsOpt.has_value());
    }

}
#endif
