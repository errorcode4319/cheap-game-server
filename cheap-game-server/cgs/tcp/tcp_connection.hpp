#pragma once 

#include <common/common.hpp>

#include <cgs/msg/messages.hpp>

namespace cgs::tcp {

class Connection; 

// Buffer 
using ConnectionBuffer = msg::SFCBuffer<Connection>;

using namespace boost;

enum class TcpConnStatus {
    kConnected = 0,
    kClosed,
    kOnError,
    kNone, 
};

class Connection : public std::enable_shared_from_this<Connection> {

public:
    Connection(
        uint64_t id, asio::io_service& ios, asio::ip::tcp::socket socket, 
        msg::MessageBuffer& msg_in, msg::MessageBuffer& msg_out) 
    : m_id(id), m_ios(ios)
    , m_socket(std::move(socket))
    , m_msg_in(msg_in)
    , m_msg_out(msg_out)
    , m_status(TcpConnStatus::kConnected)
    , m_last_error_message("")
    {
        spdlog::info("New TCP Connection => ID:{}", m_id);
    }
    
    void Run();
    void Close();
    TcpConnStatus GetStatus() const { return m_status; }

private:
    void WriteCGSMessagesAsync();
    void ReadCGSMessagesAsync();

private:    // Processes For Write Async   


private:    // Processes For Read Async 


private:
    uint64_t                m_id;
    asio::io_service&       m_ios; 
    asio::ip::tcp::socket   m_socket;
    msg::MessageBuffer&     m_msg_in;
    asio::streambuf         m_write_sbuf;
    msg::MessageBuffer&     m_msg_out;
    asio::streambuf         m_read_sbuf;
    TcpConnStatus           m_status;
    std::mutex              m_status_mutex;
    std::string             m_last_error_message;
};


}