#pragma once

#include <vulkan/vulkan.h>

namespace Noz
{
	class VulkanAPI
	{
	private:
		VkAllocationCallbacks* m_Allocator = NULL;
		VkInstance m_Instance = VK_NULL_HANDLE;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE;
		uint32_t m_QueueFamily = (uint32_t)-1;
		VkQueue m_Queue = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT m_DebugReport = VK_NULL_HANDLE;
		VkPipelineCache m_PipelineCache = VK_NULL_HANDLE;
		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;

	public:
		VulkanAPI(const char** extensions, uint32_t extensions_count);
		~VulkanAPI();

		void SetupVulkan(const char** extensions, uint32_t extensions_count);
		void CleanupVulkan();
	};
}