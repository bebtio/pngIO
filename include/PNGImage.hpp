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

    pngIO::PLTEChunk _PLTEChunk;
    pngIO::IDATChunk _IDATChunk;
    pngIO::IENDChunk _IENDChunk;
    pngIO::cHRMChunk _cHRMChunk;
    pngIO::gAMAChunk _gAMAChunk;
    pngIO::iCCPChunk _iCCPChunk;
    pngIO::sBITChunk _sBITChunk;
    pngIO::sRGBChunk _sRGBChunk;
    pngIO::bKGDChunk _nKGDChunk;
    pngIO::hISTChunk _hISTChunk;
    pngIO::tRNSChunk _tRNSChunk;
    pngIO::pHYsChunk _pHYsChunk;
    pngIO::sPLTChunk _sPLTChunk;
    pngIO::tIMEChunk _tIMEChunk;
    pngIO::iTXtChunk _iTXtChunk;
    pngIO::tEXtChunk _tEXtChunk;
    pngIO::zTXtChunk _ztxChunk;
};