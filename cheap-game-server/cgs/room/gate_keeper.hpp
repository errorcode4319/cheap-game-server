#pragma once 

#include <common/common.hpp>
#include <cgs/tcp/tcp_connection.hpp>
#include <cgs/msg/handshake.hpp>

namespace cgs::room {

enum class GateEntryStatus {
    kSuccess = 0,
    kHSTimeout,
    kHSInvalidMessage,
    kHSInvalidClient,
};

class GateKeeper {

public:
    GateKeeper(
        tcp::SharedConnBuffer& buf_check_in, 
        tcp::SharedConnBuffer& buf_accept_out)
    : m_buf_check_in(buf_check_in)
    , m_buf_accept_out(buf_accept_out)
    , m_is_running(false)
    {}

    void Run(size_t num_threads = 1);

    void Shutdown();

private:
    void Process(int tid);

    GateEntryStatus Handshake(tcp::SharedConn& conn);

    tcp::SharedConn GetNextClientConn();

    void AcceptClientConn(tcp::SharedConn conn);

    void DeclineClientConn(tcp::SharedConn conn, const std::string& message);


private:
    bool        m_is_running;
    size_t      m_num_threads;
    std::mutex  m_conn_mutex; 
    std::vector<std::thread>    m_threads;

    // Unidentified Connection Buffer (input)
    tcp::SharedConnBuffer& m_buf_check_in;

    // Accepted Connection Buffer (output)
    tcp::SharedConnBuffer& m_buf_accept_out;
};

}