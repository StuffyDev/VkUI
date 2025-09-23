#include "Application.hpp"
#include "Logger.hpp"

#include <cstdlib>
#include <stdexcept>

int main() {
    try {
        Application app{800, 600, "VkUI Engine"};
        app.run();
    } catch (const std::exception& e) {
        Log::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
