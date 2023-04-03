#include "user_events.hpp"

void UserEvents::Update() {

    RefreshKeyStates();

    while (SDL_PollEvent(&m_event)) {
        switch(m_event.type) {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            UpdateKeyPressed(m_event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            UpdateKeyReleased(m_event.key.keysym.sym);
            break;
        default:
            break; 
        }
    }

}

void UserEvents::RefreshKeyStates() {
    for(auto& state: m_key_state) {
        if (state & KeyState::kRelease) {
            state = KeyState::kNone; 
        }
        else if(state & KeyState::kPress) {
            state = KeyState::kHold;
        }
    }
}

void UserEvents::UpdateKeyPressed(int key) {
    auto& state = m_key_state[key];
    if (state & KeyState::kNone) {
        state = KeyState::kPress | KeyState::kHold;
    }
    else {
        state = KeyState::kHold;
    }
    state |= KeyState::kUpdate;
}

void UserEvents::UpdateKeyReleased(int key) {
    auto& state = m_key_state[key];
    if (state & KeyState::kHold) {
        state = KeyState::kRelease;
    }
    state |= KeyState::kUpdate;
}
