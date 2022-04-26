#include "pch.h"
#include "EntityAdmin.hpp"

using namespace Noz;

EntityAdmin::~EntityAdmin()
{
	DestoryAllSysytems();
	DestroyAllEntities();
}

void EntityAdmin::Update(float time_step)
{
	for (BaseSystem* s : systems_) {
		s->Update(time_step);
	}
}

Entity * EntityAdmin::FindEntity(EntityID eid)
{
	auto it = entities_.find(eid);
	return (it == entities_.end()) ? nullptr : it->second;
}

void EntityAdmin::DestroyEntity(EntityID eid)
{
	auto it = entities_.find(eid);
	if (it != entities_.end())
	{
		delete it->second;
		entities_.erase(it);
	}
}

void EntityAdmin::DestoryAllSysytems()
{
	for (BaseSystem* sys : systems_)
	{
		delete sys;
	}
	systems_.clear();
}

void EntityAdmin::DestroyAllEntities()
{
	for (auto& kv : entities_)
	{
		delete kv.second;
	}
	entities_.clear();
}

ComponentVector& EntityAdmin::GetAllComponents(index_t id)
{
	return component_pool_.GetAllComponents(id);
}
