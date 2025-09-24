#include "Application.hpp"
#include "Logger.hpp"
#include "VulkanEngine.hpp"
#include <stdexcept>
#include <utility>

Application::Application(int width, int height, std::string title, std::string html, std::string css)
    : m_width(width), 
      m_height(height), 
      m_title(std::move(title)), 
      m_htmlContent(std::move(html)),
      m_cssContent(std::move(css)),
      m_window(nullptr) {
    Log::info("Application created.");
    m_vulkanEngine = std::make_unique<VulkanEngine>();
}

Application::~Application() {
    teardown();
    Log::info("Application destroyed.");
}

void Application::run() {
    setupWindow();
    m_vulkanEngine->init(m_window, m_htmlContent, m_cssContent); // <-- Передаем контент
    mainLoop();
}

void Application::setupWindow() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (!glfwInit()) throw std::runtime_error("GLFW init failed");
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) throw std::runtime_error("GLFW window creation failed");
}

void Application::mainLoop() {
    Log::info("Starting main loop...");
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        m_vulkanEngine->drawFrame();
    }
    Log::info("Main loop finished.");
    vkDeviceWaitIdle(m_vulkanEngine->getDevice());
}

void Application::teardown() {
    if (m_window) glfwDestroyWindow(m_window);
    glfwTerminate();
    Log::info("Window and GLFW terminated.");
}
