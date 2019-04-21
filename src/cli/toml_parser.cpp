/**
 * @file toml_parser.cpp
 * @author Khoi Trinh
 * @brief
 * @version 0.1
 * @date 2019-04-07
 *
 * @copyright Copyright Khoi Trinh (c) 2019
 *
 */
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "toml11/toml.hpp"

// #include "config_builder.hpp"
#include "raw_config_parser.hpp"
#include "utils.hpp"

// #include "cpptoml.hpp"

// static void logInit(const std::string& buildDir) {
//     auto logPath = buildDir + "/logs/" + "pre_build.log";

//     auto consoleLog = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//     consoleLog->set_level(spdlog::level::warn);
//     auto fileLog = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath, true);
//     fileLog->set_level(spdlog::level::debug);
//     std::vector<spdlog::sink_ptr> logs{consoleLog, fileLog};
//     // TODO(kd): Change log format
//     // TODO(kd): Route parser error to stdout and then to file

//     auto logger = std::make_shared<spdlog::logger>("pre_build_log", logs.begin(), logs.end());
//     spdlog::set_default_logger(logger);
//     spdlog::info("hatter log initialized");
// }

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    auto data = toml::parse(argv[1]);
    hatter::BasicConfig basicConfig;
    hatter::getBasicConfig(data, basicConfig);
    std::cout << basicConfig.osName << std::endl;

    // const auto rawBasicConfig = toml::get<toml::Table>(data.at("basic"));
    // const auto title = toml::get<std::string>(rawBasicConfig.at("mock_env_fedora_version"));
    // std::cout << rawBasicConfig << std::endl;
    // std::cout << "the mock env version is " << title << std::endl;

    // auto& testTable = toml::get<toml::Table>(data.at("basic"));
    // toml::table testTable;
    // auto        res = hatter::getTOMLTable(data, "basic", testTable);

    // std::string testVal;
    // res &= hatter::getTOMLVal<std::string>(testTable, "base_spin", testVal, "BASIC");
    // if (!res) {
    //     std::cout << "Failed to get table" << std::endl;
    //     exit(1);
    // }
    // std::cout << testVal << std::endl;

    
    // const auto testStr   = toml::get<toml::string>(testTable.at("mock_env_fedora_version"));
    // if (testTable.is_ok()) {
    //     std::cout << "test table is valid" << std::endl;
    // } else {
    //     std::cout << "test table is invalid" << std::endl;
    // }
    // testStr = "20";
    // testTable["mock_env_fedora_version"] = "20";
    // std::cout << data.at("basic") << std::endl;

    // nums = [1, 2, 3, 4, 5]
    // std::vector<int> nums = toml::get<std::vector<int>>(data.at("nums"));
    // std::cout << "the length of `nums` is" << nums.size() << std::endl;

    // std::cout << "Current path is " << getExeDir() << std::endl;
    // auto buildDir = hatter::getExeDir() + "/build";

    // try {
    //     logInit(buildDir);
    //     auto rawConfig     = cpptoml::parse_file(argv[1]);
    //     auto isValidConfig = true;

    //     std::shared_ptr<cpptoml::table> rawBasicConfig;
    //     hatter::BasicConfig             basicConfig;

    //     isValidConfig &= hatter::getTOMLTable(rawConfig.get(), "basic", rawBasicConfig);
    //     if (rawBasicConfig) {
    //         isValidConfig &= hatter::getBasicConfig(rawBasicConfig.get(), basicConfig);
    //     }

    //     if (!isValidConfig) {
    //         spdlog::error("Invalid configuration, exitting");
    //         return 1;
    //     }

    //     hatter::buildMockConfig(basicConfig, buildDir);
    // } catch (const cpptoml::parse_exception& e) {
    //     std::cerr << "Failed to parse setting file: " << argv[1] << ": " << e.what() <<
    //     std::endl; return 1;
    // }

    return 0;
}
