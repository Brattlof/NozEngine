#pragma once

#include <map>
#include <memory>
#include <vector>
#include "../Utils/Functional.hpp"
#include "../BaseComponent/BaseComponent.hpp"

namespace Noz
{
	class BaseComponent;
	using ComponentVector = std::vector<BaseComponent*>;
    class ComponentPool
    {
	private:
        std::map<index_t, ComponentVector> component_pools_;

    public:
        template <class C, typename... Args>
        BaseComponent* CreateComponent(Args&&... args);
		void RemoveComponent(index_t id, BaseComponent* component);

        ComponentVector& GetAllComponents(index_t id);
    };

    template <class C, typename... Args>
    BaseComponent* ComponentPool::CreateComponent(Args&&... args)
    {
        ComponentVector& pool = GetAllComponents(Details::ComponentIndex::index<C>());
        BaseComponent* component = new C();
        (static_cast<C*>(component))->Reset(std::forward<Args>(args)...);
        pool.push_back(component);
        return component;
    }
}