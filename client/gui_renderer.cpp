#include "gui_renderer.hpp"

bool GUIRenderer::InitWindow(const std::string& title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to init sdl" << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (m_window == nullptr) {
        std::cerr << "Failed to create window" << std::endl;
        return false; 
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        std::cout << "Failed to create renderer" << std::endl;
        return false; 
    }
    SDL_SetRenderDrawColor(m_renderer, 255,255,255,255);

    return true; 
}

bool GUIRenderer::InitFont() {
    if (TTF_Init() != 0) {
        std::cerr << "Failed to init sdl fft" << std::endl;
        return false;
    }
    return true;
}


int GUIRenderer::AddFont(const std::string& fontfile, size_t fontsize) {
    TTF_Font* p_font = TTF_OpenFont(fontfile.c_str(), fontsize);
    if (p_font == nullptr) {
        std::cerr << "Failed to add font: " << fontfile << std::endl;
        std::cerr << TTF_GetError() << std::endl;
        return -1;
    } 
    m_font_arr.push_back(p_font);
    return m_font_arr.size() - 1;
}

void GUIRenderer::RenderBegin() {
    SDL_RenderClear(m_renderer);
    m_on_render = true; 

}

void GUIRenderer::RenderEnd() {
    SDL_RenderPresent(m_renderer);
    m_on_render = false; 
}

bool GUIRenderer::RenderText(int font_id, const std::string& text, int x, int y, SDL_Color color) {
    if (m_font_arr.size() <= font_id) {
        std::cerr << "Invalid Font ID" << std::endl;
        return false;
    }
    auto font = m_font_arr[font_id];
    SDL_Surface* p_text_surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (p_text_surface == nullptr) {
        std::cerr << "Failed to create Text Surface" << std::endl;
        return false;
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(m_renderer, p_text_surface);
    if (p_texture == nullptr) {
        std::cerr << "Failed to create Texture from text surface" << std::endl;
        SDL_FreeSurface(p_text_surface);
        return false; 
    }
    SDL_Rect draw_rect;
    draw_rect.x = x;
    draw_rect.y = y;
    draw_rect.w = p_text_surface->w;
    draw_rect.h = p_text_surface->h;
    SDL_RenderCopy(m_renderer, p_texture, nullptr, &draw_rect);


    // TODO: Reuse Surface&Texture Instances 
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_text_surface);
    return true; 
}

void GUIRenderer::Release() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    for (auto p_font : m_font_arr) {
        if (p_font) TTF_CloseFont(p_font);
    }
    TTF_Quit();
    SDL_Quit();
}