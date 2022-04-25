#include "VulkanAPI.hpp"

using namespace Noz;

void VulkanAPI::SetupVulkan(const char** extensions, uint32_t extensions_count)
{
	VkResult err;

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.enabledExtensionCount = extensions_count;
    create_info.ppEnabledExtensionNames = extensions;

    err = vkCreateInstance(&create_info, m_Allocator, &m_Instance);
}