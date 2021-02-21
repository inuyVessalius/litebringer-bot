cmake_minimum_required(VERSION 3.17)
project(litebringer_bot)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/dependencies" "${PROJECT_SOURCE_DIR}/include")
add_subdirectory(dependencies)

add_executable(auto_clicker src/main.cpp src/litebringer_bot.cpp)
target_link_libraries(auto_clicker opencv_world451d opencv_world451)
