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
}