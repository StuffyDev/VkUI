#pragma once

#include <vulkan/vulkan.h>
#include <optional>

// A struct to hold the queue family indices we need.
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
};

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
    void createLogicalDevice();

    // Helper functions
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);

    VkInstance m_instance;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device;           // The logical device
    VkQueue m_graphicsQueue;    // Handle to the graphics queue
};
