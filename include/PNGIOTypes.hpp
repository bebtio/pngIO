#pragma once

#include <array>

namespace pngIO
{
    // PNG file signature defined by standard.
    const std::array<uint8_t,8> signature = {137, 80, 78, 71, 13, 10, 26, 10};


    // PNG Type codes that lead each PNGChunk.
    // More info of each chunk can be found here: http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.Additional-chunk-types
    enum class TypeCodes : uint32_t
    {
        IHDR = 0x49484452, // Image header.
        PLTE = 0x504c5445, // Palette.
        IDAT = 0x49444154, // Image data.
        IEND = 0x49454e44, // Image trailer.
        cHRM = 0x6348524d, // Primary chromaticities. 
        gAMA = 0x67414d41, // Image gamma.
        iCCP = 0x69434350, // Embedded ICC profile.
        sBIT = 0x73424954, // Significant bits.
        sRGB = 0x73524742, // Standard RGB color space.
        bKGD = 0x624b4744, // Background color.
        hIST = 0x68495354, // Palette histogram.
        tRNS = 0x74524e53, // Transparency.
        pHYs = 0x70485973, // Physical Pixel Dimensions.
        sPLT = 0x73504c54, // Suggested palette.
        tIME = 0x74494d45, // Image last modification time.
        iTXt = 0x69545874, // International textual data.
        tEXt = 0x74455874, // Textual data.
        zTXt = 0x7a545874  // Compressed textual data.
    };
}