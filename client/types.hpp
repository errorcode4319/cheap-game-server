#pragma once 

#include <cstdint>

struct Vector2f {
    float x;
    float y;
};

struct Coord {
    int x = 0;
    int y = 0;
};

struct Size {
    int width = 0;
    int height = 0;
};

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

struct Circle {
    int x;
    int y;
    int radius;
};