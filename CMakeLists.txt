cmake_minimum_required(VERSION 3.0)
project(cheap-game-server)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SRC_PATH ./cheap-game-server)
file(GLOB SOURCES ${SRC_PATH}/*.cpp ${SRC_PATH}/*.hpp)

add_executable(cgs ${SOURCES})

target_include_directories(
    # Target 
    cgs PRIVATE 

    # Header-Only 3rdparty libs 
    3rdparty/argparse-v2.9/include 
    3rdparty/fmt-v9.1.0/include 
    3rdparty/spdlog-v1.11.0/include 
)