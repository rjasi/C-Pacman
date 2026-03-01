#pragma once
#include <cstddef>

namespace Pacman::EnumHelper
{
    template <typename E>
    constexpr auto toIndex(E e)
    {
        return static_cast<std::size_t>(e);
    }
}