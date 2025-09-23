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
    void pickPhysicalDevice();
    
    // Helper function to check if a device is suitable
    bool isDeviceSuitable(VkPhysicalDevice device);

    VkInstance m_instance;
    VkPhysicalDevice m_physicalDevice; // Handle for the selected GPU
};
