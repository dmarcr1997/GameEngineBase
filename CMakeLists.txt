cmake_minimum_required(VERSION 3.31)
project(GameBasecamp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:\\SDL3\\SDL3-3.2.18\\x86_64-w64-mingw32\\lib\\cmake")

find_package(SDL3 REQUIRED CONFIG)

add_executable(GameBasecamp main.cpp
        Game.cpp
        Game.h)

target_link_libraries(GameBasecamp PRIVATE SDL3::SDL3)

add_custom_command(TARGET GameBasecamp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/SDL3/SDL3-3.2.18/x86_64-w64-mingw32/bin/SDL3.dll"
        $<TARGET_FILE_DIR:GameBasecamp>)

