cmake_minimum_required(VERSION 3.0)
project(cheap-game-server)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(
    # Header-Only 3rdparty libs 
    3rdparty/argparse-v2.9/include 
    3rdparty/fmt-v9.1.0/include 
    3rdparty/spdlog-v1.11.0/include 
)

# Server 
add_subdirectory(cheap-game-server)

# Client 
add_subdirectory(client)