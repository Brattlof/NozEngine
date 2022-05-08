#include "pch.hpp"
#include "Application.hpp"
#include "../FileManager/FileManager.hpp"
#include <filesystem>

using namespace Noz;

std::unique_ptr<Window> m_Window;

Application::Application(const char* title, int width, int height, bool use_imgui)
{
	FileManager::Init();

	m_Window = std::make_unique<Window>(title, width, height, use_imgui);
}

Application::~Application()
{
	FileManager::Cleanup();
}

bool Application::Run()
{
	if (!m_Window->Alive())
		return false;

	m_Window->Update();

	return true;
}