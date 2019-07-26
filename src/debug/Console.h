//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_DEBUG_CONSOLE_H_
#define AZOR_SRC_DEBUG_CONSOLE_H_

#include <imgui/imgui.h>

class Console
{
    char                  InputBuf[256]{};
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;

 private:
    static int   Stricmp(const char* str1, const char* str2);
    static int   Strnicmp(const char* str1, const char* str2, int n);
    static char* Strdup(const char *str);
    static void  Strtrim(char* str);

    void    ClearLog();

    void    ExecCommand(const char* command_line);

    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);

    int     TextEditCallback(ImGuiInputTextCallbackData* data);

 public:
    Console();
    ~Console();

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void    Draw(const char* title, bool* p_open);
};

#endif //AZOR_SRC_DEBUG_CONSOLE_H_
