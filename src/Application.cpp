#include "Application.hpp"
#include "Logger.hpp"
#include <stdexcept>

Application::Application(int width, int height, std::string title)
    : m_width(width), m_height(height), m_title(std::move(title)), m_window(nullptr) {
    Log::info("Application created.");
}

Application::~Application() {
    teardown();
    Log::info("Application destroyed.");
}

void Application::run() {
    setupWindow();
    mainLoop();
}

void Application::setupWindow() {
    // This hint is crucial for compatibility, especially on Linux with Wayland.
    // It forces GLFW to use the X11 backend, which is more stable for Vulkan.
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        Log::error("Failed to initialize GLFW");
        throw std::runtime_error("GLFW init failed");
    }

    // Tell GLFW not to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // For now, let's keep the window non-resizable
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        Log::error("Failed to create GLFW window");
        throw std::runtime_error("GLFW window creation failed");
    }
    Log::info("Window created successfully.");
}

void Application::mainLoop() {
    Log::info("Starting main loop...");
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        // Drawing will happen here
    }
    Log::info("Main loop finished.");
}

void Application::teardown() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        Log::info("Window destroyed.");
    }
    glfwTerminate();
    Log::info("GLFW terminated.");
}
