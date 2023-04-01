#include "application.hpp"


Application::Application() {
    
}

Application::~Application() {

}

bool Application::Init() {
    // Center Enable, Fullscreen Disable
    if (!m_gui.InitWindow("GUI Client", 0, 0, 1280, 740)){
        std::cerr << "Failed to init gui window" << std::endl; 
        return false;
    }  
    if (!m_gui.InitFont()) {
        std::cerr << "Failed to init font" << std::endl; 
        return false;
    }
    if (!m_gui.SetDefaultFont("./Consolas.ttf", 32)) {
        std::cerr << "Failed to set default font" << std::endl;
        return false;
    }
    return true;
}

bool Application::Update() {
    PollUserEvents();

    return true; 
}

void Application::PollUserEvents() {
    while (SDL_PollEvent(&m_event)) {
        switch(m_event.type) {

        case SDL_QUIT:
            m_on_quit = true;
            return;



        }
    }
}

bool Application::Render() {
    m_gui.DrawBegin();
    
    m_gui.DrawText("Test", {10, 10});
    m_gui.DrawRect(Rect{100, 100, 100, 100}, Color{255, 0, 0}, true);
    m_gui.DrawCircle(Circle{300, 300, 50}, Color{0, 255, 0}, true);
    
    m_gui.DrawEnd();

    return true; 
}

bool Application::Wait() {
    m_frame_count++;
    SDL_Delay(30);
    if (m_frame_count % 100 == 0) {
        std::cout << "Update " << m_frame_count << " Frames" << std::endl;
    }
    if (m_on_error) {
        return false; 
    }
    return !m_on_quit;
}