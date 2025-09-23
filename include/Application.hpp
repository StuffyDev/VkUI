#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

class Application {
public:
    Application(int width, int height, std::string title);
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

    GLFWwindow* m_window;
};
