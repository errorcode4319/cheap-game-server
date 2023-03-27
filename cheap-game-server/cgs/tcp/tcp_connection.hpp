#pragma once 

#include <common/common.hpp>

#include <cgs/msg/messages.hpp>

namespace cgs::tcp {

using namespace boost;

class Connection; 

using SharedConn = std::shared_ptr<Connection>;

// Buffer 
using SharedConnBuffer = msg::SFCBuffer<SharedConn>;


enum class TcpConnStatus {
    kConnected = 0,
    kClosed,
    kOnError,
    kNone, 
};

class Connection : public std::enable_shared_from_this<Connection> {

public:
    Connection(
        uint64_t id, asio::io_service& ios, asio::ip::tcp::socket socket) 
    : m_id(id), m_ios(ios)
    , m_socket(std::move(socket))
    , m_status(TcpConnStatus::kConnected)
    , m_last_error_message("")
    {
        spdlog::info("New TCP Connection => ID:{}", m_id);
    }
    
    void Run();

    void Close();

    uint64_t GetID() const { return m_id; }

    TcpConnStatus GetStatus() const { return m_status; }
    msg::MessageBuffer& GetMsgInBuf() { return m_msg_in; }
    msg::MessageBuffer& GetMsgOutBuf() { return m_msg_out; }

    bool ReadUntil(std::string& buf, char delim_c) {
        return ReadUntil(buf, std::to_string(delim_c), delim_c);
    }
    bool ReadUntilWait(std::string& msg, char delim_c, uint64_t timeout_ms = 0) {
        return ReadUntilWait(msg, std::to_string(delim_c), delim_c, timeout_ms);
    }
    bool ReadUntil(std::string& buf, const std::string& read_delim_s, char getline_delim_c);
    bool ReadUntilWait(std::string& msg, const std::string& read_delim_c, char getline_delim_c, uint64_t timeout_ms = 0);

private:
    void WriteCGSMessagesAsync();
    void ReadCGSMessagesAsync();

private:    // Processes For Write Async   


private:    // Processes For Read Async 


private:
    uint64_t                m_id;
    asio::io_service&       m_ios; 
    asio::ip::tcp::socket   m_socket;
    msg::MessageBuffer      m_msg_in;
    asio::streambuf         m_write_sbuf;
    msg::MessageBuffer      m_msg_out;
    asio::streambuf         m_read_sbuf;
    TcpConnStatus           m_status;
    std::mutex              m_status_mutex;
    std::string             m_last_error_message;
};


}