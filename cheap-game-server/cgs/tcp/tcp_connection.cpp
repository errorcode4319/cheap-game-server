#include "tcp_connection.hpp"

namespace cgs::tcp {

void Connection::Run() {

    WriteCGSMessagesAsync();
    ReadCGSMessagesAsync();

}

void Connection::Close() {
    std::scoped_lock lock(m_status_mutex);
    spdlog::info("TCP Connection Close => id: {}", m_id);
    m_status = TcpConnStatus::kClosed;
    if (m_socket.is_open()) {
        m_socket.cancel();
    }
}

void Connection::WriteCGSMessagesAsync() {

}

void Connection::ReadCGSMessagesAsync() {

}

}