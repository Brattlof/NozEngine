#include "pch.hpp"
#include "SceneAdmin.hpp"

using namespace Noz;

SceneAdmin::SceneAdmin() 
{ 
	m_Scenes;
}

SceneAdmin::~SceneAdmin()
{
	for (auto x : m_Scenes)
	{
		delete x.second;
	}
}

void SceneAdmin::AddScene(std::string name, Scene* scene)
{
	m_Scenes.emplace(name, scene);
}

Scene& SceneAdmin::GetScene(std::string name)
{
	return *m_Scenes[name];
}