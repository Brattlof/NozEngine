#pragma once

#include <vector>
#include <unordered_map>
#include "../Utils/Define.hpp"
#include "../Utils/Functional.hpp"

#include "../Entity/Entity.hpp"
#include "../BaseSystem/BaseSystem.hpp"
#include "../ComponentPool/ComponentPool.hpp"

namespace Noz
{
	class Entity;
	class EntityAdmin
	{
	private:
		std::vector<BaseSystem*> systems_;
		std::unordered_map<EntityID, Entity*> entities_;
		ComponentPool component_pool_;

	public:
		EntityAdmin() = default;
		~EntityAdmin();
		void Update(float time_step);

		template<class S>
		S& CreateSystem();
		template<class S>
		void RemoveSystem();
		template<class S>
		bool HasSystem();

		template<class E>
		Entity& CreateEntity();
		Entity* FindEntity(EntityID eid);
		void DestroyEntity(EntityID eid);

		//you can use your entity pool to generate eid
		EntityID GenerateEntityID()
		{
			static EntityID start_id = 0;
			return ++start_id;
		}

		ComponentVector& GetAllComponents(index_t id);
	private:
		void DestoryAllSysytems();
		void DestroyAllEntities();
	};

	template<class S>
	S& EntityAdmin::CreateSystem()
	{
		index_t system_index = Details::SystemIndex::index<S>();
		if (system_index >= systems_.size()) {
			systems_.resize(system_index + 1, nullptr);
		}
		S* sys = new S(this);
		systems_[system_index] = sys;
		return *sys;
	}

	template<class S>
	void EntityAdmin::RemoveSystem()
	{
		delete systems_[Details::SystemIndex::index<S>()];
		systems_[Details::SystemIndex::index<S>()] = nullptr;
	}

	template<class S>
	bool EntityAdmin::HasSystem()
	{
		return systems_.size() > Details::SystemIndex::index<S>() && systems_[Details::SystemIndex::index<S>()] != nullptr;
	}

	template<class E>
	Entity& EntityAdmin::CreateEntity()
	{
		EntityID eid = GenerateEntityID();
		Entity* ent = new E(component_pool_, eid);
		entities_.insert(std::make_pair(eid, ent));
		return *ent;
	}

}