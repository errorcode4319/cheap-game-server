#include "gui_renderer.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool g_is_running = false;

int main(int argc, char* args[]) {

    GUIRenderer gui;
    gui.InitWindow("GUI Client", 0, 0, 640, 480, false);
    gui.InitFont();
    auto font_id = gui.AddFont("./Consolas.ttf", 16);
    if (font_id == -1) return 0;
    g_is_running = true;

    while(g_is_running) {

        gui.RenderBegin();
        gui.RenderText(font_id, "Test", 10, 10);
        gui.RenderEnd();
    
    }

    return 0;
}