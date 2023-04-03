#pragma once 

#include <cstdint>
#include "types.hpp"

class Player {

public:
    Player(uint64_t id): m_id(id) {};
    ~Player() {};

    uint64_t GetId() const { return m_id; };

    void MoveX(float dist) {m_pos.x += dist;}
    void MoveY(float dist) {m_pos.y += dist;}

    Vector2f GetPos() const { return m_pos; }
    void SetPos(const Vector2f& pos) { m_pos = pos; }
    
    float GetRenderRadian() const { return m_render_radian; }
    void SetRenderRadian(float radian) { m_render_radian = radian; }

    Color GetRenderColor() const { return m_render_color; }
    void SetRenderColor(Color color) { m_render_color = color; }

private:
    const uint64_t  m_id;
    Vector2f        m_pos;

    float           m_render_radian;
    Color           m_render_color;
};