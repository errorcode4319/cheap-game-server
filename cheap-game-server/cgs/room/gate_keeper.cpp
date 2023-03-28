#include "gate_keeper.hpp"

namespace cgs::room {

void GateKeeper::Run(size_t num_threads) {
    m_is_running = true; 
    m_num_threads = num_threads;
    for (size_t i = 0;i < num_threads; i++) {
        std::thread t{&GateKeeper::Process, this, i};
        m_threads.push_back(std::move(t));
    }
}

void GateKeeper::Shutdown() {
    m_is_running = false; 
}

void GateKeeper::Process(int tid) {
    while (m_is_running) {
        auto conn = GetNextClientConn();

        if (conn == nullptr) continue;

        spdlog::info("GateKeeper: Load Client Connection => id: ", conn->GetID());
        std::string hs_msg;
        uint64_t timeout_ms = 5000;
        auto success = conn->ReadUntilWait(hs_msg, "\n\r", '\n', timeout_ms);
        if (!success) {
            DeclineClientConn(std::move(conn), fmt::format("Message Read Timeout: {}ms", timeout_ms)); 
            continue;
        }
        spdlog::info("Message From Client\n{}", hs_msg);
        success = conn->ReadUntilWait(hs_msg, "\n\r", '\n', timeout_ms);
        if (success) {
            spdlog::info("Message From Client\n{}", hs_msg);
        }
    }
}

tcp::SharedConn GateKeeper::GetNextClientConn() {
    std::scoped_lock lock(m_conn_mutex);
    //  no waiting, if not empty 
    m_buf_check_in.Wait();
    if (m_buf_check_in.Empty()) 
        return nullptr;
    auto t = m_buf_check_in.PopFront();
    return t; 
}

void GateKeeper::AcceptClientConn(tcp::SharedConn conn) {
    
    //m_buf_accept_out.PushBack(std::move(conn));
}

void GateKeeper::DeclineClientConn(tcp::SharedConn conn, const std::string& message) {
    
    spdlog::info("Decline Client: {}", message);
}



}