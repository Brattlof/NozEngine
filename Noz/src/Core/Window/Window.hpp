#pragma once

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Noz
{
	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

	public:
		Window(const char* title, int width, int height, bool use_imgui = false);
		~Window();

		void Update();

		bool Setup(const char* title, int width, int height, bool use_imgui);
		void Cleanup();
		bool Alive();
	};
}