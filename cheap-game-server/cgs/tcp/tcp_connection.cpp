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

bool Connection::ReadUntil(std::string& buf, const std::string& read_delim_s, char delim_c) {
    try {
        asio::read_until(m_socket, m_read_sbuf, read_delim_s);
        std::getline(m_read_stream, buf, delim_c);
    }
    catch (const boost::system::system_error& e) {
        spdlog::error("Read Error Code: {}, Message: {}", e.code().value(), e.what());
        return false; 
    }
    return true;
}

bool Connection::ReadUntilWait(std::string& msg, const std::string& read_delim_s, char getline_delim_c, uint64_t timeout_ms) {

    asio::async_read_until(
        m_socket, m_read_sbuf, read_delim_s,
        [this](const system::error_code& ec, size_t bytes_transferred) {
            if (ec.value() != 0) {
                spdlog::error("Connection: ReadWait Error => Code: {}, Message: {}", ec.value(), ec.message());
            }
            m_read_wait_cv.notify_one();
        }
    );
    {
        std::unique_lock<std::mutex> lock(m_read_wait_mutex);
        if (m_read_wait_cv.wait_for(lock, std::chrono::milliseconds(timeout_ms)) == std::cv_status::timeout) {
            spdlog::warn("Failed to read, timeout");
            m_socket.cancel();
            return false; 
        }
    }
    std::getline(m_read_stream, msg, getline_delim_c);
    return true;
}

void Connection::WriteCGSMessagesAsync() {

}

void Connection::ReadCGSMessagesAsync() {

}

}