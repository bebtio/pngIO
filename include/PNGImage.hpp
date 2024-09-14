#pragma once

#include "PNGFile.hpp"
#include "PNGIOTypes.hpp"

class PNGImage
{

public:
    PNGImage( const PNGFile &pngFile );
    PNGImage( const std::string &filename );
    ~PNGImage() {}


    // I might end up moving all this stuff below here to PNGFile. That sort
    // of makes more sense.
    // I think all this file should have a is a vector of "pixel" data
    // with stuff from the image header.
    //
    // Getters and setters incoming.
    // There are 17 chunk types. So 17 getters and 17 setters.

    // Getters
    pngIO::IHDRChunk getIHDRChunk() const { return _IHDRChunk; }
    pngIO::PLTEChunk getPLTEChunk() const { return _PLTEChunk; }
    pngIO::IDATChunk getIDATChunk() const { return _IDATChunk; }
    pngIO::IENDChunk getIENDChunk() const { return _IENDChunk; }
    pngIO::cHRMChunk getcHRMChunk() const { return _cHRMChunk; }
    pngIO::gAMAChunk getgAMAChunk() const { return _gAMAChunk; }
    pngIO::iCCPChunk getiCCPChunk() const { return _iCCPChunk; }
    pngIO::sBITChunk getsBITChunk() const { return _sBITChunk; }
    pngIO::sRGBChunk getsRGBChunk() const { return _sRGBChunk; }
    pngIO::bKGDChunk getbKGDChunk() const { return _nKGDChunk; }
    pngIO::hISTChunk gethISTChunk() const { return _hISTChunk; }
    pngIO::tRNSChunk gettRNSChunk() const { return _tRNSChunk; }
    pngIO::pHYsChunk getpHYsChunk() const { return _pHYsChunk; }
    pngIO::sPLTChunk getsPLTChunk() const { return _sPLTChunk; }
    pngIO::tIMEChunk gettIMEChunk() const { return _tIMEChunk; }
    pngIO::iTXtChunk getiTXtChunk() const { return _iTXtChunk; }
    pngIO::tEXtChunk gettEXtChunk() const { return _tEXtChunk; }
    pngIO::zTXtChunk getzTXtChunk() const { return _ztxtChunk; }

    // Setters
    void setIHDRChunk(const pngIO::IHDRChunk& chunk) { _IHDRChunk = chunk; }
    void setPLTEChunk(const pngIO::PLTEChunk& chunk) { _PLTEChunk = chunk; }
    void setIDATChunk(const pngIO::IDATChunk& chunk) { _IDATChunk = chunk; }
    void setIENDChunk(const pngIO::IENDChunk& chunk) { _IENDChunk = chunk; }
    void setcHRMChunk(const pngIO::cHRMChunk& chunk) { _cHRMChunk = chunk; }
    void setgAMAChunk(const pngIO::gAMAChunk& chunk) { _gAMAChunk = chunk; }
    void setiCCPChunk(const pngIO::iCCPChunk& chunk) { _iCCPChunk = chunk; }
    void setsBITChunk(const pngIO::sBITChunk& chunk) { _sBITChunk = chunk; }
    void setsRGBChunk(const pngIO::sRGBChunk& chunk) { _sRGBChunk = chunk; }
    void setbKGDChunk(const pngIO::bKGDChunk& chunk) { _nKGDChunk = chunk; }
    void sethISTChunk(const pngIO::hISTChunk& chunk) { _hISTChunk = chunk; }
    void settRNSChunk(const pngIO::tRNSChunk& chunk) { _tRNSChunk = chunk; }
    void setpHYsChunk(const pngIO::pHYsChunk& chunk) { _pHYsChunk = chunk; }
    void setsPLTChunk(const pngIO::sPLTChunk& chunk) { _sPLTChunk = chunk; }
    void settIMEChunk(const pngIO::tIMEChunk& chunk) { _tIMEChunk = chunk; }
    void setiTXtChunk(const pngIO::iTXtChunk& chunk) { _iTXtChunk = chunk; }
    void settEXtChunk(const pngIO::tEXtChunk& chunk) { _tEXtChunk = chunk; }
    void setzTXtChunk(const pngIO::zTXtChunk& chunk) { _ztxtChunk = chunk; }

private:

    PNGFile _pngFile;
};