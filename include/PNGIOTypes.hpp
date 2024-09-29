#pragma once

#include <array>
#include <cstdint>
#include "PNGChunk.hpp"

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
        zTXt = 0x7a545874, // Compressed textual data.
        INVALID = 0x0
    };

    enum class ColorType: uint8_t
    {
        grayScale  = 0,
        rgb        = 2,
        pallete    = 3,
        grayScaleA = 4,
        rgba       = 6,
        INVALID    = 255
    };

    enum class BitDepth: uint8_t
    {
        one     = 1,
        two     = 2,
        four    = 4,
        eight   = 8,
        sixteen = 16,
        INVALID = 0
    };

    class PNGChunkInterface
    {
    public:

        virtual ~PNGChunkInterface() = default;
        virtual bool readFromRawPNGChunk( const PNGChunk &chunk ) = 0;
        virtual bool writeRawPNGChunk   ( PNGChunk &chunk )       = 0;

        TypeCodes getTypeCode() { return(_typeCode); }
        uint32_t  getLength()   { return (_length);  }

        void setTypeCode( pngIO::TypeCodes typeCode ) { _typeCode = typeCode; }
        void setLength( uint32_t length)              { _length   = length;   }

    protected:
        TypeCodes _typeCode;
        uint32_t  _length;
    };

    // PNG Structs follow. There is one for each TypeCode.
    // These structs break the chunk's data field into concrete data structures.
    class IHDRChunk : public PNGChunkInterface
    {
    public:
        IHDRChunk();
        ~IHDRChunk() {}
        bool readFromRawPNGChunk( const PNGChunk &chunk ) override;
        bool writeRawPNGChunk( PNGChunk &chunk ) override;
		void clear();

        // Getters
        uint32_t getWidth()             const                { return _width;             }
        uint32_t getHeight()            const                { return _height;            }
        BitDepth  getBitDepth()          const                { return _bitDepth;          }
        ColorType  getColorType()         const                { return _colorType;         }
        uint8_t  getCompressionMethod() const                { return _compressionMethod; }
        uint8_t  getFilterMethod()      const                { return _filterMethod;      }
        uint8_t  getInterlaceMethod()   const                { return _interlaceMethod;   }

        // Setters
        void setWidth(uint32_t width)                        { _width             = width;             }
        void setHeight(uint32_t height)                      { _height            = height;            }
        void setBitDepth(BitDepth bitDepth)                   { _bitDepth          = bitDepth;          }
        void setColorType(ColorType colorType)                 { _colorType         = colorType;         }
        void setCompressionMethod(uint8_t compressionMethod) { _compressionMethod = compressionMethod; }
        void setFilterMethod(uint8_t filterMethod)           { _filterMethod      = filterMethod;      }
        void setInterlaceMethod(uint8_t interlaceMethod)     { _interlaceMethod   = interlaceMethod;   }

    private:
        uint32_t _width;
        uint32_t _height;
        BitDepth  _bitDepth;
        ColorType _colorType;
        uint8_t  _compressionMethod;
        uint8_t  _filterMethod;
        uint8_t  _interlaceMethod;
    };

}
