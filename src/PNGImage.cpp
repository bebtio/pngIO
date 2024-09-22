#include "PNGImage.hpp"


PNGImage::PNGImage( const PNGFile &pngFile )
{
    // Construct the members from the raw pngFile
    // If they don't exist, give them a 0x0 typeCode.
}

PNGImage::PNGImage( const std::string &filename )
{
    // Construct the members by first creating PNGFile object,
    // then construct the members with that object.
}