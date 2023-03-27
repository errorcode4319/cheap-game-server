#include "tcp_acceptor.hpp"


namespace cgs::tcp {

void Acceptor::Run() {
    SetupAccept();
}

void Acceptor::Shutdown() {
    m_is_closed = true; 

}

void Acceptor::SetupAccept() {
    if (m_is_closed.load()) {
        m_acceptor.close();
        return;
    }

    auto shared_socket = std::make_shared<asio::ip::tcp::socket>(m_ios);
    m_acceptor.async_accept(*shared_socket.get(),
        [this, shared_socket](const system::error_code& ec){
            this->OnAccept(ec, shared_socket);   
        }
    );
}

void Acceptor::OnAccept(
    const system::error_code& ec,
    std::shared_ptr<asio::ip::tcp::socket> shared_socket
) {
    if (this->OnError(ec)) {
        return;
    }
    uint64_t conn_id = m_acc_count++;
    // Test 
    msg::MessageBuffer  msg_in, msg_out;
    auto conn = std::make_shared<Connection>(
        conn_id, m_ios, std::move(*shared_socket.get()), msg_in, msg_out);
    
    conn->Close();
    this->SetupAccept();
}

bool Acceptor::OnError(const system::error_code& ec) {
    if (ec.value() != 0) {
        spdlog::error("TCP Acceptor Error Code: {}, Message: {}", ec.value(), ec.message());
        return true;
    }
    return false; 
}

}