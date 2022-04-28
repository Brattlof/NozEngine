#pragma once

#include <ECS/ECS.hpp>

namespace Noz
{
	class Scene
	{
	private:
		EntityAdmin* m_EntityAdmin;
		std::vector<Entity*> m_EntityList;

	public:
		Scene();
		~Scene();

		EntityAdmin* GetAdmin() { return m_EntityAdmin; }

		void AddEntity(Entity* entity) { m_EntityList.push_back(entity); }
		Entity* GetEntity(uint32_t index) { return m_EntityList.at(index); }
		std::vector<Entity*> GetEntityList() { return m_EntityList; }
	};
}