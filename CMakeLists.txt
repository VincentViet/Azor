cmake_minimum_required(VERSION 3.14)
project(azor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(deps deps/catch2 deps/glm deps/GLFW src)

file(GLOB_RECURSE libraries ${PROJECT_SOURCE_DIR} "lib/*.a")
file(GLOB_RECURSE b2 ${PROJECT_SOURCE_DIR} "deps/Box2D/*.cpp" "deps/imgui/*.cpp")

file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR} "src/*.cc")

add_executable(azor ${src} ${b2})
target_link_libraries(azor ${libraries} pthread X11 dl)