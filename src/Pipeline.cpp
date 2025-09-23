#include "Pipeline.hpp"
#include "Logger.hpp"

#include <fstream>
#include <stdexcept>

Pipeline::Pipeline(VkDevice device, const std::string& vertFilepath, const std::string& fragFilepath) 
    : m_device(device) {
    Log::info("Creating pipeline with shaders: " + vertFilepath + " and " + fragFilepath);
    
    auto vertShaderCode = readFile(vertFilepath);
    auto fragShaderCode = readFile(fragFilepath);

    createShaderModule(vertShaderCode, &m_vertShaderModule);
    createShaderModule(fragShaderCode, &m_fragShaderModule);
    Log::info("Shader modules created successfully.");
}

Pipeline::~Pipeline() {
    vkDestroyShaderModule(m_device, m_vertShaderModule, nullptr);
    vkDestroyShaderModule(m_device, m_fragShaderModule, nullptr);
    Log::info("Shader modules destroyed.");
    // We will destroy the actual pipeline here later
}

std::vector<char> Pipeline::readFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        Log::error("Failed to open file: " + filepath);
        throw std::runtime_error("File open failed");
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(m_device, &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
}
