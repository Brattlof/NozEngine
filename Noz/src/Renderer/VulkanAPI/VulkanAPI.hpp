#pragma once

#include <vulkan/vulkan.h>

namespace Noz
{
	class VulkanAPI
	{
	private:
		VkAllocationCallbacks* m_Allocator;
		VkInstance m_Instance;
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_Device;
		uint32_t m_QueueFamily = (uint32_t)-1;
		VkQueue m_Queue;
		VkDebugReportCallbackEXT m_DebugReport;
		VkPipelineCache m_PipelineCache;
		VkDescriptorPool m_DescriptorPool;

	public:
		void SetupVulkan(const char** extensions, uint32_t extensions_count);
	};
}