#include "pch.hpp"
#include "../Entity/Entity.hpp"

using namespace Noz;

BaseComponent* BaseComponent::SiblingComponent(const index_t index)
{
	return ent_ ? ent_->GetComponent(index) : nullptr;
}