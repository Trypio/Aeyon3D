//
// Created by thors on 11.10.2022.
//

#ifndef AEYON3D_MOUSEBUTTON_HPP
#define AEYON3D_MOUSEBUTTON_HPP

#include <cstdint>

namespace aeyon
{
    enum class MouseButton : std::uint32_t
    {
        Left = 1,
        Middle = 2,
        Right = 3,
        Mouse5 = 4,
        Mouse4 = 5
    };
}

#endif //AEYON3D_MOUSEBUTTON_HPP
