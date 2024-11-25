cmake_minimum_required(VERSION 3.15)
project(hyperwall)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_IMPLEMENTATIONS
    src/impl/FFmpeg.cpp
    src/impl/Sources.cpp
    src/impl/Hyperwall.cpp
)
set(CMAKE_CXX_FLAGS "-O3")

# This project
include_directories(include)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(sender src/Sender.cpp ${PROJECT_IMPLEMENTATIONS})

target_link_libraries(sender
    ${OpenCV_LIBS}
    argparse
)

