#pragma once 

#include <SDL2/SDL.h>
#include <array>

namespace KeyState {

enum state: uint8_t {
    kNone       = 1 << 0,
    kHold       = 1 << 1,
    kPress      = 1 << 2,
    kRelease    = 1 << 3,

    kUpdate     = 1 << 7,   // Unused 
};

}

class UserEvents {


public:
    UserEvents() {
        for(auto& state: m_key_state) state = KeyState::kNone;
    }

    void Update();

    uint8_t GetKeyState(char key) const {
        return m_key_state[key];
    }

    bool CheckKeyState(char key, uint8_t flags) {
        return bool(m_key_state[key] & flags > 0);
    }

    bool OnQuit() const { return m_quit; }

private:
    void RefreshKeyStates();
    void UpdateKeyPressed(int key);
    void UpdateKeyReleased(int key);

    SDL_Event       m_event;
    std::array<uint8_t, 512>    m_key_state{};
    bool            m_quit{false};

};