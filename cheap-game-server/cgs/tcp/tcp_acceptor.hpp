#pragma once 

#include <common/common.hpp>
#include "tcp_connection.hpp"

namespace cgs::tcp {

class Acceptor {

public:
    Acceptor(asio::io_service& ios, uint16_t port)
    : m_ios(ios)
    , m_port(port)
    , m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port))
    , m_is_closed(false)
    , m_acc_count(0)
    {
    }

    void Run();

    void Shutdown(); 

private:
    void SetupAccept();

    void OnAccept(
        const system::error_code& ec,
        std::shared_ptr<asio::ip::tcp::socket> shared_socket);


private:
    bool OnError(const system::error_code& ec);


private:   
    asio::io_service&           m_ios;
    uint16_t                    m_port; 
    asio::ip::tcp::acceptor     m_acceptor;
    std::atomic<bool>           m_is_closed;
    uint64_t                    m_acc_count;
};

}