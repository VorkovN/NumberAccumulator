#ifndef NUMBERACCUMULATOR_APPS_SERVER_TESTS_SERVERTEST_H
#define NUMBERACCUMULATOR_APPS_SERVER_TESTS_SERVERTEST_H

#include "ServerSettingsParser.h"

namespace apps::server::tests
{
    TEST(ServerSettingsParserTest, printTest)
    {

        int argc = 2;
        std::array<char*, 2> argv{"testName", "-h"};
        auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(!settingsOpt.has_value());
    }

}
#endif
