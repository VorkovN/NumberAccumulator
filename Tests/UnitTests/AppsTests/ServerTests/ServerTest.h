#ifndef NUMBERACCUMULATOR_TESTS_SOMESERVERTEST_H
#define NUMBERACCUMULATOR_TESTS_SOMESERVERTEST_H

#include "ServerSettingsParser.h"

namespace tests
{

    TEST(ServerSettingsParserTest, printTest)
    {
        int argc = 2;
        std::array<char*, 2> argv{"testName", "-h"};
        auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(!settingsOpt.has_value());    }

}
#endif
