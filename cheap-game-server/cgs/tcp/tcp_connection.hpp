#pragma once 

#include <common/common.hpp>

#include <cgs/msg/messages.hpp>

namespace cgs::tcp {

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
    {}
    
    void Run();

    void Close();

private:
    void WriteCGSMessagesAsync();
    void ReadCGSMessagesAsync();

private:    // Processes For Write Async   
    

private:    // Processes For Read Async 


private:
    uint64_t                m_id;
    asio::io_service&       m_ios; 
    asio::ip::tcp::socket   m_socket;
    std::condition_variable m_msg_cond;
    msg::MessageBuffer&     m_msg_in;
    msg::MessageBuffer&     m_msg_out;
    TcpConnStatus           m_status;
    std::mutex              m_status_mutex;
    std::string             m_last_error_message;
};

}