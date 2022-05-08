#pragma once

#include <memory>
#include "../Window/Window.hpp"

namespace Noz
{
	class Application
	{
	private:
		std::unique_ptr<Window> m_Window;

	public:
		Application(const char* title, int width, int height, bool use_imgui = false);
		~Application();

		bool Run();
	};
}