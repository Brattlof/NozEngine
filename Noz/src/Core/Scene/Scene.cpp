#include "pch.hpp"
#include "Scene.hpp"

using namespace Noz;

Scene::Scene()
{
	m_EntityAdmin = new EntityAdmin();
	m_EntityList;
}

Scene::~Scene()
{
	delete m_EntityAdmin;
}