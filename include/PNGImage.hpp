#pragma once

#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"
#include "PNGPixel.hpp"


class PNGImage
{

public:
    PNGImage( std::vector<PNGChunk> chunks );
    PNGImage( const std::string &filename );
    ~PNGImage() {}

private:

    pngIO::IHDRChunk _imageHeader;
    pngIO::PixelVector _pvec;
};

namespace pngImageUtil 
{
    pngIO::PixelVector 
    createPixelVectorFromChunks( std::vector<PNGChunk> chunks );

    std::vector<pngIO::GrayscalePixel8>
    createGrayscalePixel8Vector( const PNGChunk& chunk );

    std::vector<pngIO::GrayscalePixel16>
    createGrayscalePixel16Vector( const PNGChunk& chunk );

    std::vector<pngIO::GrayscalePixelA8>
    createGrayscalePixelA8Vector( const PNGChunk& chunk );

    std::vector<pngIO::GrayscalePixelA16>
    createGrayscalePixelA16Vector( const PNGChunk& chunk );
    
    std::vector<pngIO::RGBPixel8>
    createRGBPixel8Vector( const PNGChunk& chunk );

    std::vector<pngIO::RGBPixel16>
    createRGBPixel16Vector( const PNGChunk& chunk );

    std::vector<pngIO::RGBAPixel8>
    createRGBAPixel8Vector( const PNGChunk& chunk );

    std::vector<pngIO::RGBAPixel16>
    createRGBAPixel16Vector( const PNGChunk& chunk );
}