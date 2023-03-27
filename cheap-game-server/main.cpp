#include <cgs/cgs.hpp>

int main(int argc, char** argv) {
    argparse::ArgumentParser parser("Cheap-Game-Server", "0.1.0");
    parser.add_argument("--tcp_port").required().scan<'i', int>()
        .default_value(666).help("Set TCP Port").metavar("<port-num>");
    parser.add_argument("--max_conn").required().scan<'i', int>()
        .default_value(1000).help("Set limit the number of connected clients").metavar("<num-limit>");
    parser.add_argument("--num_thread").required().scan<'i', int>()
        .default_value(4).help("Set size of thread pool").metavar("<thread-num>");

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
    auto num_thread = parser.get<int>("--num_thread");
    spdlog::info("Cheap Game Server Running...\nTCP Port: {}\nMax Client: {}", tcp_port, max_num_client);
    
    try {
        cgs::MainServer server;
        spdlog::info("Run Server 0.0.0.0:{}, t:{}", tcp_port, num_thread);
        server.Run(uint16_t(tcp_port), size_t(num_thread));
        
        while (true) {
            std::string command;
            std::getline(std::cin, command);
            if (command == "exit") {
                break;
            }
        }
        
        spdlog::info("Shutdown Server");
        server.Shutdown();
    }
    catch (const std::exception& e) {
        spdlog::info("{}", e.what());
    }
        
    return 0;
}