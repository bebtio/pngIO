#pragma once

#include "PNGFile.hpp"
#include "PNGIOTypes.hpp"

class PNGImage
{

public:
    PNGImage( const PNGFile &pngFile );
    PNGImage( const std::string &filename );
    ~PNGImage() {}

    // Getters and setters incoming.
    // There are 17 chunk types. So 17 getters and 17 setters.

    // Getters
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
    pngIO::zTXtChunk _ztxtChunk;
};