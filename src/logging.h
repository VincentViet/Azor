//
// Created by vice on 24/07/2019.
//

#ifndef AZOR_SRC_LOGGING_H_
#define AZOR_SRC_LOGGING_H_

#include <tinyxml2.h>
#include <spdlog/spdlog.h>

#define LOG_INFO(...)               (spdlog::info(__VA_ARGS__))
#define LOG_WARN(...)               (spdlog::warn(__VA_ARGS__))
#define LOG_ERROR(...)              (spdlog::error(__VA_ARGS__))
#define LOG_TRACE(...)              (spdlog::trace(__VA_ARGS__))
#define LOG_DEBUG(...)              (spdlog::debug(__VA_ARGS__))
#define LOG_CRITICAL(...)           (spdlog::critical(__VA_ARGS__))

namespace logging{
    void startUp(tinyxml2::XMLElement* logging);
}

#endif //AZOR_SRC_LOGGING_H_
