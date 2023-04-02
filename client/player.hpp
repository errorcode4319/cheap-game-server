#pragma once 

#include <cstdint>
#include "types.hpp"

class Player {

public:
    Player() {};
    ~Player() {};

    void MoveX(float dist) {m_pos.x += dist;}
    void MoveY(float dist) {m_pos.y += dist;}

    Vector2f GetPos() const { return m_pos; }
    void SetPos(const Vector2f& pos) { m_pos = pos; }
    
private:
    uint64_t    m_id;
    Vector2f    m_pos;
};