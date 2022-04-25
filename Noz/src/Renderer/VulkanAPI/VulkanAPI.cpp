#include "VulkanAPI.hpp"

#include <stdlib.h>

using namespace Noz;

VulkanAPI::VulkanAPI(const char** extensions, uint32_t extensions_count)
{
    SetupVulkan(extensions, extensions_count);
}

VulkanAPI::~VulkanAPI()
{
    CleanupVulkan();
}

void VulkanAPI::SetupVulkan(const char** extensions, uint32_t extensions_count)
{
    VkResult err;

    // Creating Vulkan Instance

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.enabledExtensionCount = extensions_count;
    create_info.ppEnabledExtensionNames = extensions;

    err = vkCreateInstance(&create_info, m_Allocator, &m_Instance);

    // Select GPU

    uint32_t gpu_count;
    err = vkEnumeratePhysicalDevices(m_Instance, &gpu_count, NULL);

    VkPhysicalDevice* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
    err = vkEnumeratePhysicalDevices(m_Instance, &gpu_count, gpus);

    int use_gpu = 0;
    for (int i = 0; i < (int)gpu_count; i++)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(gpus[i], &properties);
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            use_gpu = i;
            break;
        }
    }

    m_PhysicalDevice = gpus[use_gpu];
    free(gpus);
}

void VulkanAPI::CleanupVulkan()
{
    if (m_Allocator)
    {
        if (m_Device)
        {
            if (m_DescriptorPool)
            {
                vkDestroyDescriptorPool(m_Device, m_DescriptorPool, m_Allocator);
            }
            vkDestroyDevice(m_Device, m_Allocator);
        }
        vkDestroyInstance(m_Instance, m_Allocator);
    }
}