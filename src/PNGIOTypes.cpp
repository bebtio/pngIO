#include "PNGIOTypes.hpp"
#include "PNGChunk.hpp"
#include <cstdint>


pngIO::IHDRChunk::IHDRChunk()
{
    clear();
}

void pngIO::IHDRChunk::clear()
{
    _typeCode          = TypeCodes::INVALID;
    _length            = 0;
    _width             = 0;
    _height            = 0;
    _bitDepth          = 0;
    _colorType         = 0;
    _compressionMethod = 0;
    _filterMethod      = 0;
    _interlaceMethod   = 0;
}

bool
pngIO::IHDRChunk::readFromRawPNGChunk( const PNGChunk &chunk )
{
    bool succeeded(false);
    size_t offset(0);

    _typeCode = static_cast<TypeCodes>(chunk.getTypeCode());

    if( _typeCode == pngIO::TypeCodes::IHDR )
    {
        _length   = chunk.getLength();

        std::vector<std::byte> data = chunk.getData();

        _width             = *reinterpret_cast<uint32_t*>(data.data() + offset ); offset += 4;
        _height            = *reinterpret_cast<uint32_t*>(data.data() + offset ); offset += 4;

        // Convert to host byte order.
        _width             = ntohl(_width);
        _height            = ntohl(_height);

        _bitDepth          = *reinterpret_cast<uint8_t*>(data.data() + offset ); offset += 1;
        _colorType         = *reinterpret_cast<uint8_t*>(data.data() + offset ); offset += 1;
        _compressionMethod = *reinterpret_cast<uint8_t*>(data.data() + offset ); offset += 1;
        _filterMethod      = *reinterpret_cast<uint8_t*>(data.data() + offset ); offset += 1;
        _interlaceMethod   = *reinterpret_cast<uint8_t*>(data.data() + offset ); offset += 1;

        succeeded = true;
    }
    else
    {
        clear();
        succeeded = false;
    }


    return(succeeded);
}

bool
pngIO::IHDRChunk::writeRawPNGChunk( PNGChunk &chunk )
{
    bool succeded(false);

    return(succeded);
}