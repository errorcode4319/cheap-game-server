#pragma once 

#include <common/common.hpp>

namespace cgs::msg {

enum class ClientType {
    kTcp = 0,   // Normal Type 
    kWebSocket,
};

struct HSPackage {
    std::string type;
    std::string id;
    std::string key;
    std::string protocol = "CGSP/0.1";
};

bool LoadHSPackFromMessage(HSPackage& hs_pack, const std::string& client_message);

bool CheckHSPack(const HSPackage& hs_pack);

}