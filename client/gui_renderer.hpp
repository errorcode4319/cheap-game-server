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

    bool InitWindow(const std::string& title, int x, int y, int width, int height, bool center, bool fullscreen);
    
    bool InitFont();
    bool SetDefaultFont(const std::string& fontfile, size_t fontsize);
    int AddFont(const std::string& fontfile, size_t fontsize);
    
    void DrawBegin();
    void DrawEnd();

    bool DrawText(const std::string& text, Coord pt, Color color = {0, 0, 0}, int font_id = -1); // Use Default Font, if font_id = -1 

    bool OnDrawing() const { return m_on_drawing; }

    void Release(); 

private:
    bool                    m_on_drawing = false;
    std::vector<TTF_Font*>  m_font_arr;
    int                     m_default_font_id = -1;
    SDL_Window*             m_window;
    SDL_Renderer*           m_renderer;

};