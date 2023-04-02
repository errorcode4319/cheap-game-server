#pragma once 

#include "gui_renderer.hpp"
#include "types.hpp"
#include "player.hpp"

class Application {

public:
    Application();
    ~Application();

    bool Init();

    bool Update();

    bool Render();

    bool Wait();

    bool IsOnError() const { return m_on_error; }
    const std::string& GetLastErrorMessage() const { return m_last_error_message; } 

private:

    void PollUserEvents();

    void Error(const std::string& error_message) {
        m_on_error = true;
        m_last_error_message = error_message;
    }

    GUIRenderer m_gui;
    bool        m_on_quit = false;
    uint64_t    m_frame_count = -1;
    uint64_t    m_prev_render_time_ms = 0;
    SDL_Event   m_event;

    bool        m_on_error = false;
    std::string m_last_error_message = "";

};