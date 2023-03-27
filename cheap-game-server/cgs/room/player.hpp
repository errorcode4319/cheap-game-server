#pragma once 

#include <common/common.hpp>
#include <cgs/tcp/tcp_connection.hpp>

namespace cgs::room {

class Player;

using PlayerQueue = msg::SFCBuffer<Player>; 

class Player {

public:
    Player(uint64_t id, const tcp::SharedConn& conn)
    : m_id(id)
    , m_conn(conn)
    {}

    uint64_t GetID() const { return m_id; }

private:
    uint64_t            m_id; 
    tcp::SharedConn     m_conn;
};

}