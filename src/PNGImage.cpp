#include <variant>
#include <iostream>

#include "PNGImage.hpp"
#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"


PNGImage::PNGImage( std::vector<PNGChunk> chunks )
{
    // Construct the members from the raw pngFile
    // If they don't exist, give them a 0x0 typeCode.
}

PNGImage::PNGImage( const std::string &filename )
{
    // Construct the members by first creating PNGFile object,
    // then construct the members with that object.
}

pngIO::PixelVector 
pngImageUtil::createPixelVectorFromChunks( std::vector<PNGChunk> chunks )
{
    PNGChunk header;
    PNGChunk image;

    for( const PNGChunk &c : chunks )
    {
        if( c.getTypeCode() == static_cast<uint32_t>(pngIO::TypeCodes::IHDR) )
        {
            header = c;
        }
        else if( c.getTypeCode() == static_cast<uint32_t>(pngIO::TypeCodes::IDAT) )
        {
            image = c;
        }
    }

    // If the header or image is invalid, return empty variant.
    if( !header.isValid() )
    {
        return std::monostate{};
    }

    if( !image.isValid() )
    {
        return std::monostate{};
    }

    pngIO::IHDRChunk ihdr;
    ihdr.readFromRawPNGChunk(header);

    if( ihdr.getColorType() == pngIO::ColorType::grayScale )
    {

    }
    else if ( ihdr.getColorType() == pngIO::ColorType::grayScaleA )
    {

    }
    else if( ihdr.getColorType() == pngIO::ColorType::rgb )
    {

    }
    else if( ihdr.getColorType() == pngIO::ColorType::rgba )
    {

    }
    else
    {
        std::cout << __FILE__ << ":" << __LINE__ << ": ColorType " << static_cast<uint8_t>(ihdr.getColorType()) << " is not currently supported" << std::endl;
        return std::monostate{};
    }
}