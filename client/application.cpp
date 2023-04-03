#include "application.hpp"


Application::Application() {
    
}

Application::~Application() {

}

bool Application::Init() {
    // Center Enable, Fullscreen Disable
    if (!m_gui.InitWindow("GUI Client", 0, 0, m_frame_width, m_frame_height)){
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

    m_player_info_font = m_gui.AddFont("./Consolas.ttf", 20);
    InitPlayerList();

    return true;
}

bool Application::Update() {
    m_events.Update(); 

    UpdatePlayerList();

    return true; 
}

bool Application::Render() {
    m_gui.DrawBegin();

    auto draw_player = [this] (const Player& p) {
        std::stringstream info; info << "Player ID: " << p.GetId();
        auto[fx, fy] = p.GetPos();
        auto rad = p.GetRenderRadian();
        auto color = p.GetRenderColor();
        m_gui.DrawText(info.str(), Coord{int(fx - rad), int(fy - rad - 15)}, Color{0, 0, 0}, m_player_info_font);
        m_gui.DrawCircle(Circle{int(fx), int(fy), int(rad)}, color, true);
    };
    
    m_gui.DrawText("[SPACE] - Player Select", {10, 10});
    
    for(const auto& p: m_player_list) {
        draw_player(p);
    }

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
    return !m_events.OnQuit();
}

namespace {

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 9999);

}


void Application::InitPlayerList() {
    auto gen_init_pos = [this](int inner_offset) -> Vector2f {
        int x = inner_offset + dis(gen) % (m_frame_width - inner_offset * 2);
        int y = inner_offset + dis(gen) % (m_frame_height - inner_offset * 2);
        return Vector2f{float(x), float(y)};
    };

    for(int i = 0;i < m_max_player; i++) {
        Player p(i);
        p.SetPos(gen_init_pos(100));
        p.SetRenderRadian(20);
        p.SetRenderColor(Color{50, 50, 50});
        m_player_list.emplace_back(std::move(p));
    }

    m_cur_player = m_max_player - 1;
    SelectNextPlayer();
}

void Application::UpdatePlayerList() {

    if (m_events.GetKeyState(' ') & KeyState::kPress) {
        SelectNextPlayer(); 
    }

    auto& p = m_player_list[m_cur_player];
    if (m_events.CheckKeyState('w', KeyState::kHold)) {
        m_player_list[m_cur_player].MoveY(5.0);
    }
    if (m_events.CheckKeyState('s', KeyState::kHold)) {
        m_player_list[m_cur_player].MoveY(-5.0);
    }
    if (m_events.CheckKeyState('a', KeyState::kHold)) {
        m_player_list[m_cur_player].MoveX(5.0);
    }
    if (m_events.CheckKeyState('d', KeyState::kHold)) {
        m_player_list[m_cur_player].MoveX(-5.0);
    }
}

void Application::SelectNextPlayer() {
    m_player_list[m_cur_player].SetRenderColor({50, 50, 50});
    m_cur_player = (m_cur_player + 1) % m_max_player;
    m_player_list[m_cur_player].SetRenderColor({255, 0, 0});
}
