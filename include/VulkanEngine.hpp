#pragma once

#include <vulkan/vulkan.h>

class VulkanEngine {
public:
    VulkanEngine();
    ~VulkanEngine();

    // Make it non-copyable
    VulkanEngine(const VulkanEngine&) = delete;
    VulkanEngine& operator=(const VulkanEngine&) = delete;
    
    void init();

private:
    void createInstance();
    void setupDebugMessenger();
    void pickPhysicalDevice();

    VkInstance m_instance;
};
