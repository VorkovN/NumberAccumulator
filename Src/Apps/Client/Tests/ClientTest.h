#ifndef NUMBERACCUMULATOR_APPS_CLIENT_TESTS_CLIENTTEST_H
#define NUMBERACCUMULATOR_APPS_CLIENT_TESTS_CLIENTTEST_H

#include "ClientSettingsParser.h"

namespace apps::client::tests
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

