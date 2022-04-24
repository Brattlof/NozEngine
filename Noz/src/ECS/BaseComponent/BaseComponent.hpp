#pragma once

#include "../Utils/Functional.hpp"

namespace Noz
{
	class Entity;
    class BaseComponent
    {
    protected:
		Entity* ent_{ nullptr };

    public:
		BaseComponent() = default;
        virtual ~BaseComponent() = default;

		void SetOwner(Entity* ent) { ent_ = ent; }
		Entity* Owner() { return ent_; }

        template <typename C>
        C* As();
        template <typename C>
        C const* As() const;

		template<class C>
		C* Sibling();

	private:
		BaseComponent* SiblingComponent(const index_t index);
    };

	template <typename C>
	C* BaseComponent::As()
	{
		return static_cast<C*>(this);
	}

	template <typename C>
	C const* BaseComponent::As() const
	{
		return static_cast<C*>(this);
	}

	template<class C>
	C* BaseComponent::Sibling()
	{
		BaseComponent* component = SiblingComponent(Details::ComponentIndex::index<C>());
		return component ? component->As<C>() : nullptr;
	}
}
