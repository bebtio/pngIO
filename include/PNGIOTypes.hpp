#pragma once

#include <array>

namespace pngIO
{
    // PNG file signature defined by standard.
    const std::array<uint8_t,8> signature = {137, 80, 78, 71, 13, 10, 26, 10};


    // PNG Type codes that lead each PNGChunk.
    enum class TypeCodes : uint32_t
    {
        IHDR = 0x0, // TODO: fill in this type code. // Image Header.
        PLTE = 0x0, // TODO: fill in this type code. // Pallete.
        IDAT = 0x0, // TODO: fill in this type code. // Image data.
        IEND = 0x49454e44 // Image trailer.
    };
}