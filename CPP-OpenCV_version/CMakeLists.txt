cmake_minimum_required(VERSION 2.8)
project( cifar )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Set global flags for all build types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set flags specifically for the Debug build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable( cifar main.cpp )
target_link_libraries( cifar ${OpenCV_LIBS} )
