#pragma once 

#include "tcp/tcp_acceptor.hpp"

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
    std::vector<std::thread> m_thread_pool;
};

}