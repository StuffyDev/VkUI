#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

class Pipeline {
public:
    Pipeline(VkDevice device, const std::string& vertFilepath, const std::string& fragFilepath);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
    
    // Will be needed later to bind it before drawing
    // VkPipeline getGraphicsPipeline() const { return m_graphicsPipeline; }

private:
    VkDevice m_device; // Need a reference to the logical device to destroy objects
    VkPipeline m_graphicsPipeline;
    VkShaderModule m_vertShaderModule;
    VkShaderModule m_fragShaderModule;

    // Helper to create shader modules
    static std::vector<char> readFile(const std::string& filepath);
    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
};
