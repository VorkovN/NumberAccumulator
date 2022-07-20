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

    TEST(ClientSettingsParserTest, applyTcpSettingsTest)
    {
        const size_t argc = 7;
        std::array<char*, argc> argv{"testName", "-i", "192.168.90.2", "-p", "1024", "-t", "tcp"};
        auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(settingsOpt.has_value());

        apps::client::ClientSettings referenceSettings{"192.168.90.2", 1024, apps::client::ClientSettings::Transport::TCP };
        ASSERT_EQ(referenceSettings.serverIp, settingsOpt.value().serverIp);
        ASSERT_EQ(referenceSettings.serverPort, settingsOpt.value().serverPort);
        ASSERT_EQ(referenceSettings.transport, settingsOpt.value().transport);
    }

    TEST(ClientSettingsParserTest, applyUdpSettingsTest)
    {
        const size_t argc = 7;
        std::array<char*, argc> argv{"testName", "-i", "192.168.90.3", "-p", "1025", "-t", "udp"};
        auto settingsOpt = apps::client::ClientSettingsParser::getSettings(argc, argv.data());
        ASSERT_TRUE(settingsOpt.has_value());

        apps::client::ClientSettings referenceSettings{"192.168.90.3", 1025, apps::client::ClientSettings::Transport::UDP };
        ASSERT_EQ(referenceSettings.serverIp, settingsOpt.value().serverIp);
        ASSERT_EQ(referenceSettings.serverPort, settingsOpt.value().serverPort);
        ASSERT_EQ(referenceSettings.transport, settingsOpt.value().transport);
    }

}
#endif
