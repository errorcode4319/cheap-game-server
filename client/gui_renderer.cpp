#include "gui_renderer.hpp"

bool GUIRenderer::InitWindow(const std::string& title, int x, int y, int width, int height, Color bg_color, bool center, bool fullscreen) {
    int flags = 0;
    if (fullscreen) { 
        flags = SDL_WINDOW_FULLSCREEN; 
    }
    if (center) {
        x = SDL_WINDOWPOS_CENTERED; 
        y = SDL_WINDOWPOS_CENTERED; 
    }

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
    SetDefaultBGColor(bg_color);
    DrawClean();
    return true; 
}

bool GUIRenderer::InitFont() {
    if (TTF_Init() != 0) {
        std::cerr << "Failed to init sdl fft" << std::endl;
        return false;
    }
    return true;
}

bool GUIRenderer::SetDefaultFont(const std::string& fontfile, size_t fontsize) {
    auto font_id = AddFont(fontfile, fontsize);
    if (font_id == -1) {
        return false; 
    }
    m_default_font_id = font_id;
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

void GUIRenderer::SetDefaultBGColor(Color color) {
    m_default_bg_color.r = color.r;
    m_default_bg_color.g = color.g;
    m_default_bg_color.b = color.b;
    m_default_bg_color.a = 255;
}

void GUIRenderer::DrawBegin() {
    SDL_RenderClear(m_renderer);
    m_on_drawing = true; 
}

void GUIRenderer::DrawEnd() {
    const auto&[r, g, b, a] = m_default_bg_color;
    SDL_SetRenderDrawColor(m_renderer, r, g, b, b);
    SDL_RenderPresent(m_renderer);
    m_on_drawing = false; 
}

void GUIRenderer::DrawClean() {
    DrawBegin();
    DrawEnd(); 
}

bool GUIRenderer::DrawRect(Rect rect, Color color, bool fill) {
    
    SDL_Rect render_rect;
    render_rect.x = rect.x;
    render_rect.y = rect.y;
    render_rect.w = rect.width;
    render_rect.h = rect.height;

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);

    if (fill) {
        SDL_RenderFillRect(m_renderer, &render_rect);
    }
    else {
        SDL_RenderDrawRect(m_renderer, &render_rect);
    }

    return true;
}

bool GUIRenderer::DrawText(const std::string& text, Coord pt, Color color, int font_id) {
    // User Default Font
    if (font_id == -1) {
        font_id = m_default_font_id;
        if (font_id == -1) {
            std::cerr << "Failed to set font, no default font" << std::endl;
            return false; 
        }
    }

    const auto& [x, y] = pt;
    if (m_font_arr.size() <= font_id || font_id < 0) {
        std::cerr << "failed to set font, invalid font id" << std::endl;
        return false;
    }
    auto font = m_font_arr[font_id];
    const auto&[r, g, b] = color;
    SDL_Color text_fg_rgb{r, g, b};
    SDL_Surface* p_text_surface = TTF_RenderText_Blended(font, text.c_str(), text_fg_rgb);
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