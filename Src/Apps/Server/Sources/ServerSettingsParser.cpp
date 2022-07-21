#include "ServerSettingsParser.h"

#include <getopt.h>
#include <iostream>

namespace apps::server
{

    void ServerSettingsParser::usage()
    {
        std::cout << "Options:"                                       << std::endl;
        std::cout << "-h, --help                Shows this help text" << std::endl;
        std::cout << "-i, --tcp-ip 127.0.0.1    Self tcp ip"          << std::endl;
        std::cout << "-p, --tcp-port 1234       Self tcp port"        << std::endl;
        std::cout << "-I, --udp-ip 127.0.0.1    Self udp ip"          << std::endl;
        std::cout << "-P, --udp-port 5678       Self udp port"        << std::endl;
    }

    std::optional<ServerSettings> ServerSettingsParser::getSettings(int argc, char **argv)
    {
        optind = 1;

        ServerSettings settings;

        const char* optstring = "hi:p:I:P:";
        struct option long_opts[] = {
                {"help",     no_argument,       nullptr, 'h'},
                {"tcp-ip",   required_argument, nullptr, 'i'},
                {"tcp-port", required_argument, nullptr, 'p'},
                {"udp-ip",   required_argument, nullptr, 'I'},
                {"udp-port", required_argument, nullptr, 'P'},
                {nullptr, 0, nullptr, 0}
        };

        int c = 0;
        while ((c = getopt_long(argc, argv, optstring, long_opts, nullptr)) >= 0)
        {
            switch (c)
            {
                case 'i': {
                    settings.tcpSelfIp = optarg;
                    break;
                }
                case 'p': {
                    settings.tcpSelfPort = std::stoul(optarg);
                    break;
                }
                case 'I': {
                    settings.udpSelfIp = optarg;
                    break;
                }
                case 'P': {
                    settings.udpSelfPort = std::stoul(optarg);
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