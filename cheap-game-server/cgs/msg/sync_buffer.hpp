#pragma once 

#include <common/common.hpp>

namespace cgs::msg {

template<typename T>
class SFCBuffer {   // Sync Flow-Control Buffer 

using DTYPE = std::enable_if_t<std::is_default_constructible_v<T>, T>;

public: // Flow Control 

    bool Wait(uint64_t timeout_ms=5000) {
        while(Empty() && !m_is_shutdown) {
            std::unique_lock lock(m_wait_mutex);
            m_wait_cv.wait_for(lock, std::chrono::milliseconds(timeout_ms));
        }
        return !m_is_shutdown;
    }

    void WakeUp() {
        std::unique_lock lock(m_wait_mutex);
        m_wait_cv.notify_all();
    }

    void Shutdown() {
        m_is_shutdown = true; 
        this->WakeUp(); 
    }

public: // Data Control 

    const T& GetFront() {
        std::scoped_lock lock(m_buf_mutex);
        if (m_msg_buf.size() == 0) {
            spdlog::warn("Failed to get front element, buffer is empty");
            return T{};
        }
        return m_msg_buf.front();
    }

    const T& GetBack() {
        std::scoped_lock lock(m_buf_mutex);
        if (m_msg_buf.size() == 0) {
            spdlog::warn("Failed to get back element, buffer is empty");
            return T{};
        }
        return m_msg_buf.back();
    }

    T PopFront() {
        std::scoped_lock lock(m_buf_mutex);
        if (m_msg_buf.size() == 0) {
            spdlog::warn("Failed to pop front element, buffer is empty");
            return T{};
        }
        auto e = std::move(m_msg_buf.front());
        m_msg_buf.pop_front();
        return e;
    }

    T PopBack() {
        std::scoped_lock lock(m_buf_mutex);
        if (m_msg_buf.size() == 0) {
            spdlog::warn("Failed to pop back element, buffer is empty");
            return T{};
        }
        auto e = std::move(m_msg_buf.back());
        m_msg_buf.pop_back();
        return e; 
    }

    void PushFront(const T& e) {
        std::scoped_lock lock(m_buf_mutex);
        m_msg_buf.push_front(std::move(e));
        this->WakeUp();
    }

    void PushBack(const T& e) {
        std::scoped_lock lock(m_buf_mutex);
        m_msg_buf.push_back(std::move(e));
        this->WakeUp(); 
    }

    bool Empty() {
        std::scoped_lock lock(m_buf_mutex);
        return m_msg_buf.empty();
    }

    size_t GetSize() {
        std::scoped_lock lock(m_buf_mutex);
        return m_msg_buf.size(); 
    }

    void Clear() {
        std::scoped_lock lock(m_buf_mutex);
        std::deque<T> empty_buf;
        m_msg_buf.swap(empty_buf);
    }


private:
    bool            m_is_shutdown = false;
    std::deque<T>   m_msg_buf;
    std::mutex      m_buf_mutex;
    std::mutex      m_wait_mutex; 
    std::condition_variable     m_wait_cv;
};

}