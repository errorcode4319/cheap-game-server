#include "gui_renderer.hpp"

constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

bool g_is_running = false;

int main(int argc, char* args[]) {

    GUIRenderer gui;
    // Center Enable, Fullscreen Disable
    if (!gui.InitWindow("GUI Client", 0, 0, 1280, 740)){
        std::cerr << "Failed to init gui window" << std::endl; 
        return 0;
    }  
    if (!gui.InitFont()) {
        std::cerr << "Failed to init font" << std::endl; 
        return 0;
    }
    if (!gui.SetDefaultFont("./Consolas.ttf", 32)) {
        std::cerr << "Failed to set default font" << std::endl;
        return 0;
    }
    

    gui.DrawBegin();
    
    gui.DrawText("Test", {10, 10});
    gui.DrawRect(Rect{100, 100, 100, 100}, Color{255, 0, 0}, true);
    
    gui.DrawEnd();

    SDL_Delay(3000);

    return 0;
}