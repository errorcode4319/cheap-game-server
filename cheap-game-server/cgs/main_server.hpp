#pragma once 

#include "tcp/tcp_acceptor.hpp"
#include "room/gate_keeper.hpp"

using namespace boost; 

namespace cgs {

class MainServer {

public:
    MainServer() {
        m_work.reset(new asio::io_service::work(m_ios));
    }

    void Run(uint16_t port, size_t num_threads);

    void Shutdown();

private:
    asio::io_service    m_ios;
    uint16_t            m_port;
    size_t              m_num_threads;

    std::unique_ptr<asio::io_service::work> m_work;   
    std::unique_ptr<tcp::Acceptor>          m_acceptor;
    std::unique_ptr<room::GateKeeper>       m_gate_keeper;
    std::vector<std::thread> m_thread_pool;

    // Buffer Acceptor to Gate Keeper 
    tcp::SharedConnBuffer   m_buf_acc2gk;

    // Buffer Gate Keeper to Romm Manager 
    tcp::SharedConnBuffer   m_buf_gk2rm;
};

}