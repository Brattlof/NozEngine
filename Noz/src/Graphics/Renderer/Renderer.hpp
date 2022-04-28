#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <ECS/ECS.hpp>

namespace Noz
{
	class Renderer
	{
	public:
		static void Render(std::vector<Entity*> entity_list);
	};
}