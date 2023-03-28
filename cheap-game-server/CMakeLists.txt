file(GLOB_RECURSE SOURCES
    ./**.cpp
    ./**.hpp)

# Server 
add_executable(server ${SOURCES})

target_include_directories(
    # Target 
    server PRIVATE 
    # Source Directory 
    ./
)