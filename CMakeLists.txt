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
find_package(argparse REQUIRED)

# spdlog
find_package(spdlog REQUIRED)

# catch2
find_package(Catch2 REQUIRED)

# httplib
find_package(httplib QUIET)

# init all executables
foreach(exe Sender Receiver)
    add_executable(${exe} src/${exe}.cpp ${PROJECT_IMPLEMENTATIONS})
    
    # Linking
    target_link_libraries(${exe}
        ${OpenCV_LIBS}
        argparse::argparse
        spdlog::spdlog
    )
endforeach()

# optionally compile the UI
if (httplib_FOUND)
    add_executable(SenderWeb src/SenderWeb.cpp ${PROJECT_IMPLEMENTATIONS})
    target_link_libraries(SenderWeb
        ${OpenCV_LIBS}
        argparse::argparse
        spdlog::spdlog
        httplib::httplib
    )
endif()

# Tests
enable_testing()
foreach(test ffmpeg utils hyperwall settings)
    add_executable(test_${test} src/test/${test}.cpp ${PROJECT_IMPLEMENTATIONS})
    target_link_libraries(test_${test}
        ${OpenCV_LIBS}
        spdlog::spdlog
        Catch2::Catch2WithMain
    )
    add_test(NAME ${test} COMMAND test_${test})
endforeach()
