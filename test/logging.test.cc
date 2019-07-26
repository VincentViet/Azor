//
// Created by vice on 24/07/2019.
//

#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

TEST_CASE("spdlog", "[LOGGING]"){

    auto console = spdlog::stdout_color_mt("console");
    auto logger = console.get();
    logger->set_pattern("%^[%H:%M:%S] %@:%!: %v%$");
    logger->set_level(spdlog::level::trace);

    logger->info("this is info log");
    logger->warn("this is warn log");
    logger->error("this is error log: {1}, {0}", "first", "second");
    logger->trace("this is trace log");
    logger->debug("this is debug log");
    logger->critical("this is critical log");
}