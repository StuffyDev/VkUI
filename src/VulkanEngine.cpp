#include "VulkanEngine.hpp"
#include "Logger.hpp"

#include <stdexcept>
#include <vector>
#include <string>

#include <GLFW/glfw3.h>

VulkanEngine::VulkanEngine() 
    : m_instance(VK_NULL_HANDLE), m_physicalDevice(VK_NULL_HANDLE) {
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
    pickPhysicalDevice();
}

void VulkanEngine::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VkUI Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
        Log::error("Failed to create Vulkan instance!");
        throw std::runtime_error("Vulkan instance creation failed");
    }
    Log::info("Vulkan instance created successfully.");
}

void VulkanEngine::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        Log::error("Failed to find GPUs with Vulkan support!");
        throw std::runtime_error("No Vulkan-compatible GPUs found");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    Log::info("Found " + std::to_string(deviceCount) + " GPU(s).");

    // Find a suitable device
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            m_physicalDevice = device;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) {
        Log::error("Failed to find a suitable GPU!");
        throw std::runtime_error("No suitable GPU found");
    }

    // Log the name of the selected device for clarity
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);
    Log::info("Selected physical device: " + std::string(deviceProperties.deviceName));
}

bool VulkanEngine::isDeviceSuitable(VkPhysicalDevice device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    // We are looking for a queue family that supports graphics operations
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            return true; // Found one!
        }
    }

    return false; // No graphics queue family found
}
