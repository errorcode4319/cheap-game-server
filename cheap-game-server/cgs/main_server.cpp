#include "main_server.hpp"

namespace cgs {

void MainServer::Run(uint16_t port, size_t num_threads) {
    m_port = port;
    m_num_threads = num_threads; 

    m_acceptor = std::make_unique<tcp::Acceptor>(m_ios, port);
    m_acceptor->Run();

    for (size_t i=0;i < num_threads; i++ ) {
        std::thread t{
            [this]{this->m_ios.run();}
        };
        m_thread_pool.push_back(std::move(t));
    }

}

void MainServer::Shutdown() {
    m_acceptor->Shutdown();
    m_ios.stop();

    for (auto& t: m_thread_pool) {
        t.join();
    }
}

}