#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

// Forward declaration
class VulkanEngine;

class Application {
public:
    Application(int width, int height, std::string title, std::string html, std::string css); // <-- Изменили
    ~Application();

    // Make it non-copyable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void setupWindow();
    void mainLoop();
    void teardown();

    const int m_width;
    const int m_height;
    std::string m_title;
    std::string m_htmlContent; // <-- Добавили
    std::string m_cssContent;  // <-- Добавили

    GLFWwindow* m_window;
    std::unique_ptr<VulkanEngine> m_vulkanEngine;
};
