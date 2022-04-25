#include "Application.hpp"

using namespace Noz;

Application::Application(const char* title, int width, int height, bool use_imgui) :
	m_Title(title),
	m_Width(width),
	m_Height(height)
{
	if (!this->Setup(use_imgui))
	{
		glfwTerminate();
	}
}

Application::~Application()
{
	glfwTerminate();
}

bool Application::Setup(bool use_imgui)
{
	return true;
}