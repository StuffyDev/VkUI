#include "Application.hpp"
#include "Logger.hpp"
#include "VulkanEngine.hpp" // Include our new engine
#include <stdexcept>
#include <utility>

Application::Application(int width, int height, std::string title)
    : m_width(width), m_height(height), m_title(std::move(title)), m_window(nullptr) {
    Log::info("Application created.");
    m_vulkanEngine = std::make_unique<VulkanEngine>();
}

Application::~Application() {
    teardown();
    Log::info("Application destroyed.");
}

void Application::run() {
    setupWindow();
    m_vulkanEngine->init(); // Initialize Vulkan after the window
    mainLoop();
}

void Application::setupWindow() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        Log::error("Failed to initialize GLFW");
        throw std::runtime_error("GLFW init failed");
    }
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
    // Vulkan engine will be destroyed automatically by unique_ptr
    if (m_window) {
        glfwDestroyWindow(m_window);
        Log::info("Window destroyed.");
    }
    glfwTerminate();
    Log::info("GLFW terminated.");
}
