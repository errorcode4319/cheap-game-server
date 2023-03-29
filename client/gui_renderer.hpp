#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cstdint>
#include <iostream>
#include "types.hpp"


class GUIRenderer {

public:
    GUIRenderer() {};
    ~GUIRenderer() { Release(); };

    bool InitWindow(const std::string& title, int x, int y, int width, int height, bool fullscreen);
    
    bool InitFont();
    int AddFont(const std::string& fontfile, size_t fontsize);
    
    void DrawBegin();
    void DrawEnd();

    bool DrawText(int font_id, const std::string& text, int x, int y, SDL_Color color = {0, 0, 0});

    bool OnDrawing() const { return m_on_drawing; }

    void Release(); 

private:
    bool                    m_on_drawing = false;
    std::vector<TTF_Font*>  m_font_arr;
    SDL_Window*             m_window;
    SDL_Renderer*           m_renderer;

};