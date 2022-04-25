#include "Application.hpp"

using namespace Noz;

Application::Application(const char* title, int width, int height, bool use_imgui) :
	m_Title(title),
	m_Width(width),
	m_Height(height)
{
	if (!this->Setup(title, width, height, use_imgui))
	{
		if (this->m_Window)
		{
			glfwDestroyWindow(this->m_Window);
		}

		glfwTerminate();
	}
}

Application::~Application()
{
	glfwDestroyWindow(this->m_Window);
	glfwTerminate();
}

void Application::Update()
{
	glfwSwapBuffers(this->m_Window);
	glfwGetFramebufferSize(this->m_Window, &this->m_Width, &this->m_Height);
	glfwPollEvents();
}

bool Application::Setup(const char* title, int width, int height, bool use_imgui)
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	this->m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!glfwVulkanSupported())
	{
		return false;
	}

	return true;
}

bool Application::Alive()
{
	return !glfwWindowShouldClose(this->m_Window) ? true : false;
}