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
		Cleanup();
	}
}

Window::~Window()
{
	Cleanup();
}

void Window::Update()
{
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