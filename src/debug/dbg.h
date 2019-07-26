//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_DEBUG_DBG_H_
#define AZOR_SRC_DEBUG_DBG_H_

#include <imgui/imgui.h>

namespace debug{
    void startUp();
    void update();
    void draw();
    void drawRect(const ImVec2& upper_left, const ImVec2& bottom_right, ImU32 color);
    void drawRectFiled(const ImVec2& upper_left, const ImVec2& bottom_right, ImU32 color);

    void log(const char* fmt, ...);

    void shutdown();
}

#endif //AZOR_SRC_DEBUG_DBG_H_
