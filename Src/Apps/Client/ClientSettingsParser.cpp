#include "ClientSettingsParser.h"

#include <getopt.h>
#include <iostream>

namespace apps::client
{
    std::optional<ClientSettings::Transport> ClientSettingsParser::parseTransport(const std::string& transportStr)
    {
        if (transportStr == "tcp")
            return ClientSettings::Transport::TCP;
        if (transportStr == "udp")
            return ClientSettings::Transport::UDP;
        return {};
    }

    void ClientSettingsParser::usage()
    {
        std::cout << "Options:"                                           << std::endl;
        std::cout << "-h, --help                    Shows this help text" << std::endl;
        std::cout << "-i, --ip 127.0.0.1            Server Ip"            << std::endl;
        std::cout << "-p, --port 1234               Server Port"          << std::endl;
        std::cout << "-t, --transport [tcp, udp]    Server Port"          << std::endl;
    }

    std::optional<ClientSettings> ClientSettingsParser::getSettings(int argc, char **argv)
    {
        ClientSettings settings;

        const char* optstring = "hi:p:t:";
        struct option long_opts[] = {
                {"help",      no_argument,       nullptr, 'h'},
                {"ip",        required_argument, nullptr, 'i'},
                {"port",      required_argument, nullptr, 'p'},
                {"transport", required_argument, nullptr, 't'},
                {nullptr, 0, nullptr, 0}
        };

        int c = 0;
        while ((c = getopt_long(argc, argv, optstring, long_opts, nullptr)) >= 0)
        {
            switch (c)
            {
                case 'i': {
                    settings.serverIp = optarg;
                    break;
                }
                case 'p': {
                    settings.serverPort = std::stoul(optarg);
                    break;
                }
                case 't': {
                    auto transport = parseTransport(optarg);
                    if (!transport) return {};
                    settings.transport = transport.value();
                    break;
                }
                case 'h': {
                    usage();
                    return {};
                }
                default: {
                    std::cout << "Wrong argument. Print -h or --help " << std::endl;
                    return {};
                }
            }
        }
        return settings;
    }
}