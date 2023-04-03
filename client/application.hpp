#pragma once 

#include "gui_renderer.hpp"
#include "types.hpp"
#include "user_events.hpp"
#include "player.hpp"

#include <sstream>
#include <random>

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
    void InitPlayerList();
    void SelectNextPlayer();

    void Error(const std::string& error_message) {
        m_on_error = true;
        m_last_error_message = error_message;
    }

    GUIRenderer m_gui;
    const int   m_frame_width = 1280;
    const int   m_frame_height = 720;

    UserEvents  m_events;
    
    std::vector<Player> m_player_list;
    int             m_player_info_font = -1;
    size_t          m_cur_player;
    const size_t    m_max_player = 5;

    uint64_t    m_frame_count = -1;
    uint64_t    m_prev_render_time_ms = 0;

    bool        m_on_error = false;
    std::string m_last_error_message = "";

};