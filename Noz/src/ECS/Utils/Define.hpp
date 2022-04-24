#pragma once

#include <cstdint>
#include <vector>
#include <type_traits>
#include <cassert>

namespace Noz
{

	using EntityID = uint32_t;
	using index_t = uint32_t;
	using ComponentIndexList = std::vector<index_t>;

}