#ifndef NUMBERACCUMULATOR_TESTS_SOMESERVERTEST_H
#define NUMBERACCUMULATOR_TESTS_SOMESERVERTEST_H

#include "ServerSettingsParser.h"

namespace tests
{

    TEST(ServerSettingsParserTest, printTest)
    {
        const size_t argc = 2;
        std::array<char*, argc> argv{"testName", "-h"};
        auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(!settingsOpt.has_value());
    }

    TEST(ServerSettingsParserTest, applySettingsTest)
    {
        const size_t argc = 9;
        std::array<char*, argc> argv{"testName", "-i", "192.168.90.2", "-p", "1024", "-I", "192.168.90.3", "-P", "1025"};
        auto settingsOpt = apps::server::ServerSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(settingsOpt.has_value());

        apps::server::ServerSettings referenceSettings{"192.168.90.2", 1024, "192.168.90.3", 1025 };
        ASSERT_EQ(referenceSettings.tcpSelfIp, settingsOpt.value().tcpSelfIp);
        ASSERT_EQ(referenceSettings.tcpSelfPort, settingsOpt.value().tcpSelfPort);
        ASSERT_EQ(referenceSettings.udpSelfIp, settingsOpt.value().udpSelfIp);
        ASSERT_EQ(referenceSettings.udpSelfPort, settingsOpt.value().udpSelfPort);
    }

}
#endif
