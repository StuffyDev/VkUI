#include "VulkanEngine.hpp"
#include "Logger.hpp"

#include <stdexcept>
#include <vector>
#include <string>
#include <set>

#include <GLFW/glfw3.h>

VulkanEngine::VulkanEngine() {
    Log::info("VulkanEngine created.");
}

VulkanEngine::~VulkanEngine() {
    if (m_device) {
        vkDestroyDevice(m_device, nullptr);
        Log::info("Logical device destroyed.");
    }
    if (m_instance) {
        vkDestroyInstance(m_instance, nullptr);
        Log::info("Vulkan instance destroyed.");
    }
    Log::info("VulkanEngine destroyed.");
}

void VulkanEngine::init() {
    createInstance();
    pickPhysicalDevice();
    createLogicalDevice();
}

void VulkanEngine::createInstance() {
    // ... (This function remains unchanged, so we omit it for brevity. 
    // The cat command will overwrite the whole file anyway)
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

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);
    Log::info("Selected physical device: " + std::string(deviceProperties.deviceName));
}

void VulkanEngine::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

    // This struct describes a single queue we want to create.
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    // Vulkan uses priorities to schedule command buffer execution.
    // For a single queue, it doesn't matter much.
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // Specify device features we want to use. For now, nothing special.
    VkPhysicalDeviceFeatures deviceFeatures{};

    // The main creation struct for the logical device
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    
    // Modern Vulkan doesn't distinguish between instance and device specific layers.
    // But it's good practice to set it to 0.
    createInfo.enabledLayerCount = 0;

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        Log::error("Failed to create logical device!");
        throw std::runtime_error("Logical device creation failed");
    }
    Log::info("Logical device created successfully.");

    // Get the handle to the queue we just created
    vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
    Log::info("Graphics queue handle retrieved.");
}

bool VulkanEngine::isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);
    return indices.graphicsFamily.has_value();
}

QueueFamilyIndices VulkanEngine::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.graphicsFamily.has_value()) {
            break; // We found what we need, can stop searching
        }
        i++;
    }

    return indices;
}
