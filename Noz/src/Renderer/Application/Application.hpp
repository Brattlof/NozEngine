#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Noz
{
	class Application
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

	public:
		Application(const char* title, int width, int height, bool use_imgui = false);
		~Application();

		void Update();

		bool Setup(const char* title, int width, int height, bool use_imgui);
		bool Alive();
	};
}