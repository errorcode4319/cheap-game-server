#pragma once 

#include <common/common.hpp> 

#include "sync_buffer.hpp"

namespace cgs::msg {

namespace types {
    
enum MsgTypes: uint32_t {

    kNone = 0,
    
    kServerConnected,
    kServerDisconnected,

    kPlayerRegistered,
    kPlayerMoved,
};

};

#pragma pack(push, 1)

struct Message {
    uint32_t    id              = 0; 
    uint32_t    type            = types::kNone;
    uint64_t    len             = 0;
    uint64_t    epochtime_ms    = 0;
    std::vector<uint8_t> data   = {};  
};

#pragma pack(pop)

using MessageBuffer = SFCBuffer<Message>;

}