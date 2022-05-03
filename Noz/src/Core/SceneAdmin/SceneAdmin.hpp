#pragma once

#include "../Scene/Scene.hpp"

namespace Noz
{
	class SceneAdmin
	{
	private:
		std::map<std::string, Scene*> m_Scenes;

	public:
		SceneAdmin();
		~SceneAdmin();

		//
		void AddScene(std::string name, Scene* scene);

		//
		Scene& GetScene(std::string name);
	};
}