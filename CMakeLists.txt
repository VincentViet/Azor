cmake_minimum_required(VERSION 3.14)
project(azor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(deps deps/catch2 deps/glm deps/GLFW src)

file(GLOB_RECURSE libraries ${PROJECT_SOURCE_DIR} "lib/*.a")
file(GLOB_RECURSE render ${PROJECT_SOURCE_DIR} "src/render/*.cc" "src/render/*.h")
file(GLOB_RECURSE test ${PROJECT_SOURCE_DIR} "test/*.cc")
file(GLOB_RECURSE res ${PROJECT_SOURCE_DIR} "src/res/*.cc" "src/res/*.h")

add_library(glad SHARED src/glad/glad.c)
add_library(res SHARED ${res})
add_library(render SHARED ${render})
add_library(imgui SHARED src/imgui/imgui.cpp src/imgui/imgui_demo.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_widgets.cpp)

add_executable(azor src/main.cpp)
target_link_libraries(azor glad imgui res render ${libraries} pthread X11 dl)

add_executable(test ${test})