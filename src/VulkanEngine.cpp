#include "VulkanEngine.hpp"
#include "Logger.hpp"

#include <stdexcept>
#include <vector>

// We'll need GLFW to get the required extensions for window system integration
#include <GLFW/glfw3.h>

VulkanEngine::VulkanEngine() : m_instance(VK_NULL_HANDLE) {
    Log::info("VulkanEngine created.");
}

VulkanEngine::~VulkanEngine() {
    if (m_instance) {
        vkDestroyInstance(m_instance, nullptr);
        Log::info("Vulkan instance destroyed.");
    }
    Log::info("VulkanEngine destroyed.");
}

void VulkanEngine::init() {
    createInstance();
}

void VulkanEngine::createInstance() {
    // Application Info: tells the driver about our app. Optional, but good practice.
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VkUI Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    // Instance Create Info: the main struct for creating the instance.
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Get required extensions from GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    // For now, no validation layers
    createInfo.enabledLayerCount = 0;

    // Create the instance!
    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS) {
        Log::error("Failed to create Vulkan instance!");
        throw std::runtime_error("Vulkan instance creation failed");
    }
    Log::info("Vulkan instance created successfully.");
}
