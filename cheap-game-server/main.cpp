#include "util/util.hpp"

int main(int argc, char** argv) {
    argparse::ArgumentParser parser("Cheap-Game-Server", "0.1.0");
    parser.add_argument("--tcp_port").required().scan<'i', int>()
        .default_value(666).help("Set TCP Port").metavar("<port-num>");
    parser.add_argument("--max_conn").required().scan<'i', int>()
        .default_value(1000).help("Set limit the number of connected clients").metavar("<num-limit>");

    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& e) {
        spdlog::error("Failed to parse argument, {}", e.what());
        std::cout << parser;
        return -1;
    }
    
    auto tcp_port = parser.get<int>("--tcp_port");
    auto max_num_client = parser.get<int>("--max_conn");
    spdlog::info("Cheap Game Server Running...\nTCP Port: {}\nMax Client: {}", tcp_port, max_num_client);


    return 0;
}