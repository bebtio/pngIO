#include <cstdint>
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

    pngIO::ColorType color = ihdr.getColorType();
    pngIO::BitDepth depth = ihdr.getBitDepth();

    if( color == pngIO::ColorType::grayScale )
    {
        if( depth == pngIO::BitDepth::eight )
        {
            return( createGrayscalePixel8Vector( image ) );
        }
        else if( depth == pngIO::BitDepth::sixteen )
        {

            return( createGrayscalePixel16Vector( image ) );
        }
        else
        {
            std::cout << __FILE__ << ":" << __LINE__ << ": gray scale image of bitdepth " << static_cast<uint8_t>(depth) << " is not supported" << std::endl;
            return( std::monostate{} );
        }
    }
    else if ( color == pngIO::ColorType::grayScaleA )
    {
        if( depth == pngIO::BitDepth::eight )
        {
            return( createGrayscalePixelA8Vector( image ) );
        }
        else if( depth == pngIO::BitDepth::sixteen )
        {
            return( createGrayscalePixelA16Vector( image ) );
        }
        else
        {
            std::cout << __FILE__ << ":" << __LINE__ << ": gray scale image with alpha channel of bitdepth " << static_cast<uint8_t>(depth) << " is not supported" << std::endl;
            return( std::monostate{} );
        }
    }
    else if( color == pngIO::ColorType::rgb )
    {
        if( depth == pngIO::BitDepth::eight )
        {
            return( createRGBPixel8Vector( image ) );
        }
        else if( depth == pngIO::BitDepth::sixteen )
        {
            return( createRGBPixel16Vector( image ) );
        }
        else
        {
            std::cout << __FILE__ << ":" << __LINE__ << ": RGB image of bitdepth " << static_cast<uint8_t>(depth) << " is not supported" << std::endl;
            return( std::monostate{} );
        }
    }
    else if( color == pngIO::ColorType::rgba )
    {
        if( depth == pngIO::BitDepth::eight )
        {
            return( createRGBAPixel8Vector( image ) );
        }
        else if( depth == pngIO::BitDepth::sixteen )
        {
            return( createRGBAPixel16Vector( image ) );
        }
        else
        {
            std::cout << __FILE__ << ":" << __LINE__ << ": RGB image with alpha channel of bitdepth " << static_cast<uint8_t>(depth) << " is not supported" << std::endl;
            return( std::monostate{} );
        }
    }
    else
    {
        std::cout << __FILE__ << ":" << __LINE__ << ": ColorType " << static_cast<uint8_t>(ihdr.getColorType()) << " is not currently supported" << std::endl;
        return std::monostate{};
    }
}

std::vector<pngIO::GrayscalePixel8>
pngImageUtil::createGrayscalePixel8Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::GrayscalePixel8> image;

    return(image);
}

std::vector<pngIO::GrayscalePixel16>
pngImageUtil::createGrayscalePixel16Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::GrayscalePixel16> image;

    return(image);
}

std::vector<pngIO::GrayscalePixelA8>
pngImageUtil::createGrayscalePixelA8Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::GrayscalePixelA8> image;

    return(image);
}

std::vector<pngIO::GrayscalePixelA16>
pngImageUtil::createGrayscalePixelA16Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::GrayscalePixelA16> image;

    return(image);
}
    
std::vector<pngIO::RGBPixel8>
pngImageUtil::createRGBPixel8Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::RGBPixel8> image;

    return(image);
}

std::vector<pngIO::RGBPixel16>
pngImageUtil::createRGBPixel16Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::RGBPixel16> image;

    return(image);
}

std::vector<pngIO::RGBAPixel8>
pngImageUtil::createRGBAPixel8Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::RGBAPixel8> image;

    return(image);
}

std::vector<pngIO::RGBAPixel16>
pngImageUtil::createRGBAPixel16Vector( const PNGChunk& chunk )
{
    std::vector<pngIO::RGBAPixel16> image;

    return(image);
}