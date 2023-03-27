#include "main_server.hpp"

namespace cgs {

void MainServer::Run(uint16_t port, size_t num_threads) {
    m_port = port;
    m_num_threads = num_threads; 

    m_acceptor = std::make_unique<tcp::Acceptor>(m_ios, port, m_buf_acc2gk);
    m_gate_keeper = std::make_unique<room::GateKeeper>(m_buf_acc2gk, m_buf_gk2rm);
    m_acceptor->Run();
    m_gate_keeper->Run(num_threads);

    m_thread_pool.resize(num_threads);

    for (size_t i=0;i < num_threads; i++ ) {
        m_thread_pool[i] = std::thread{
            [this, i]{
                spdlog::info("Run IO Service Thread: {}", i);
                m_ios.run();
                spdlog::info("IO Service Thread: {} Finished", i);
            }
        };
    }

}

void MainServer::Shutdown() {
    m_buf_acc2gk.Shutdown();
    m_buf_gk2rm.Shutdown();
    m_acceptor->Shutdown();
    m_gate_keeper->Shutdown();
    m_work.reset();
    m_ios.stop();

    for (auto& t: m_thread_pool) {
        if (t.joinable())
            t.join();
    }
}

}