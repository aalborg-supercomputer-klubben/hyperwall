cmake_minimum_required(VERSION 3.15)
project(hyperwall)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_IMPLEMENTATIONS
  src/FFmpeg.cpp
  src/FileSource.cpp
  src/Hyperwall.cpp
)

# This project
include_directories(include)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(sender src/Sender.cpp ${PROJECT_IMPLEMENTATIONS})

target_link_libraries(sender ${OpenCV_LIBS})
