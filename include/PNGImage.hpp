#pragma once

#include "PNGFile.hpp"
#include "PNGIOTypes.hpp"

class PNGImage
{

public:
    PNGImage( const PNGFile &pngFile );
    PNGImage( const std::string &filename );
    ~PNGImage() {}

private:

    PNGFile _pngFile;
};