#pragma once

#include <array>

namespace pngIO
{
    // PNG file signature defined by standard.
    std::array<uint8_t,8> signature = {137, 80, 78, 71, 13, 10, 26, 10};

}