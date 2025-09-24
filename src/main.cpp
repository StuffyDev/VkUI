#include "Application.hpp"
#include "Logger.hpp"

#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

std::string readFileContents(const std::string& path) {
    std::ifstream fileStream(path);
    if (!fileStream) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

int main() {
    try {
        std::string html = readFileContents("demo.html");
        std::string css = readFileContents("demo.css");
        
        Application app{800, 600, "VkUI Engine", html, css};
        app.run();
    } catch (const std::exception& e) {
        Log::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
