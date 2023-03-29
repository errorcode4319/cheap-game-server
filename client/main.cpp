#include "application.hpp"

int main(int argc, char* args[]) {

    Application app;
    
    if (!app.Init()) {
        std::cerr << "Failed to init application" << std::endl;
        return 0;
    }

    while(app.Wait()) {
        app.Update();
        app.Render();
    }

    if (app.IsOnError()) {
        std::cerr << app.GetLastErrorMessage() << std::endl;
        return -1;
    }
    
    return 0;
}