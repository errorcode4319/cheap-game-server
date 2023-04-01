file(GLOB_RECURSE SOURCES *.cpp *.hpp)
add_executable(client ${SOURCES})


find_package(SDL2 REQUIRED)

target_include_directories(
    client PRIVATE 
    ${SDL2_INCLUDE_DIRS}
)


target_link_libraries(
    client PRIVATE 
    ${SDL2_LIBRARIES}
    /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
    /usr/lib/x86_64-linux-gnu/libSDL2_gfx.so
)