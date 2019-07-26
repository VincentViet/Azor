//
// Created by vice on 26/07/2019.
//

#include "dbg.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <window/window.h>

static bool isDebug = false;

void debug::startUp()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void debug::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

//    if (show_demo_window)
//        ImGui::ShowDemoWindow(&show_demo_window);
//
//    {
//        static int counter = 0;
//
//        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//        ImGui::Checkbox("Another Window", &show_another_window);
//
//        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//        ImGui::End();
//
//        if (show_another_window)
//        {
//            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//            ImGui::Text("Hello from another window!");
//            if (ImGui::Button("Close Me"))
//                show_another_window = false;
//            ImGui::End();
//        }
//    }

    ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Debug", nullptr))
    {
        ImGui::End();
        return;
    }
    ImGui::Checkbox("Debug draw", &isDebug);
    ImGui::End();
}

void debug::draw()
{
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void debug::drawRect(const ImVec2& upper_left, const ImVec2& bottom_right, ImU32 color)
{
    if (isDebug)
        ImGui::GetBackgroundDrawList()->AddRect(upper_left, bottom_right, color);
}

void debug::drawRectFiled(const ImVec2 &upper_left, const ImVec2 &bottom_right, ImU32 color)
{
    if (isDebug)
        ImGui::GetBackgroundDrawList()->AddRectFilled(upper_left, bottom_right, color);
}

void debug::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}