#include "pch.hpp"
#include "Window.hpp"

using namespace Noz;

Window::Window(const char* title, int width, int height, bool use_imgui) :
	m_Title(title),
	m_Width(width),
	m_Height(height)
{
	if (!Setup(title, width, height, use_imgui))
	{
		NOZ_LOG_ERROR(NOZ_OBFUSCATE("Failed to setup window"));
		Cleanup();
	}

	NOZ_LOG_INFO(NOZ_OBFUSCATE("Window setup successful"));

	while (Alive())
	{
		Update();
	}
}

Window::~Window()
{
	Cleanup();
}

void Window::Update()
{
	bgfx::reset((uint32_t)m_Width, (uint32_t)m_Height, BGFX_RESET_VSYNC);
	bgfx::setDebug(BGFX_DEBUG_STATS);
	bgfx::frame();

	glfwSwapBuffers(m_Window);
	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
	glfwPollEvents();
}

bool Window::Setup(const char* title, int width, int height, bool use_imgui)
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_Window)
	{
		return false;
	}

	bgfx::renderFrame();

	bgfx::Init init;
	init.resolution.width = (uint32_t)m_Width;
	init.resolution.height = (uint32_t)m_Height;
	init.resolution.reset = BGFX_RESET_VSYNC;

#ifdef NOZ_PLATFORM_WINDOWS
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: Windows"));
	init.platformData.nwh = glfwGetWin32Window(m_Window);

#elif defined NOZ_PLATFORM_LINUX
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: Linux"));
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_Window);

#elif defined NOZ_PLATFORM_OSX
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: OSX"));
	init.platformData.nwh = glfwGetCocoaWindow(m_Window);
#endif

	if (!bgfx::init(init))
	{
		return false;
	}

	return true;
}

void Window::Cleanup()
{
	bgfx::shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::Alive()
{
	return !glfwWindowShouldClose(this->m_Window) ? true : false;
}