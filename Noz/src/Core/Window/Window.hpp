#pragma once

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#ifdef NOZ_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32

#elif defined NOZ_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11

#elif defined NOZ_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>

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