#include "pch.hpp"
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
	delete m_VulkanAPI;
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

	uint32_t extensions_count = 0;
	const char** extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
	m_VulkanAPI = new VulkanAPI(extensions, extensions_count);

	return true;
}

bool Application::Alive()
{
	return !glfwWindowShouldClose(this->m_Window) ? true : false;
}