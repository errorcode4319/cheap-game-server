#include"handshake.hpp"

namespace cgs::msg {


/*
    Normal(TCP) Client's HS Message 
    HS <id> <key> CGSP/0.1\n\r
    - HS  => Handshake Command 
    - <id>: string client id 
    - <key>: string secret key 
    - CGSP/0.1 => protocol/version
    - ' ' Delimiter 
*/
bool LoadHSPackFromMessage(HSPackage& hspack, const std::string& client_message) {
    std::stringstream ss(client_message);
    
    if (!std::getline(ss, hspack.type, ' ')) {
        spdlog::warn("Failed to parse HS Type");
        return false; 
    }
    if (!std::getline(ss, hspack.id, ' ')) {
        spdlog::warn("Failed to parse Client ID");
        return false;
    }
    if (!std::getline(ss, hspack.key, ' ')) {
        spdlog::warn("Failed to parse Secret Key");
        return false; 
    }
    if (!std::getline(ss, hspack.protocol, '\r')) {
        spdlog::warn("Failed to parse Protocol");
        return false;
    }
    return true; 
}

bool CheckHSPack(const HSPackage& hs_pack) {
    // TODO: Update HS Key Check Logic
    if (hs_pack.type != "HS") {
        spdlog::warn("Invalid HS Type");
        return false; 
    }
    if (hs_pack.id.length() == 0) {
        spdlog::warn("Invalid Client ID");
        return false;
    }
    if (hs_pack.key != "key1234") {
        spdlog::warn("Invalid Secret Key");
        return false;
    } 
    if (hs_pack.protocol != "CGSP/0.1") {
        spdlog::warn("Invalid Protocol Info");
        return false;
    }
    return true;
}

}