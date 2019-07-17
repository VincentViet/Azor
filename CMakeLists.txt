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
file(GLOB_RECURSE tmx ${PROJECT_SOURCE_DIR} "src/tmxparser/*.cc" "src/tmxparser/*.h")
file(GLOB_RECURSE imgui ${PROJECT_SOURCE_DIR} "src/imgui/*.cpp" "src/imgui/*.h")
file(GLOB_RECURSE camera ${PROJECT_SOURCE_DIR} "src/camera/*.cc" "src/camera/*.h")
#file(GLOB_RECURSE common ${PROJECT_SOURCE_DIR} "src/common/*.cc" "src/common/*.h")


add_library(tinyxml2 SHARED src/tinyxml2/tinyxml2.cpp)
add_library(glad SHARED src/glad/glad.c)
add_library(res SHARED ${res})
add_library(camera SHARED ${camera})

add_library(render SHARED ${render})
target_link_libraries(render camera)
#add_library(common SHARED ${common})

add_library(tmx SHARED ${tmx})
target_link_libraries(tmx tinyxml2 #[[common]])

add_library(imgui SHARED ${imgui})

add_executable(azor src/main.cpp)
target_link_libraries(azor tmx glad imgui res render ${libraries} pthread X11 dl)

add_executable(test ${test})
target_link_libraries(test tmx)