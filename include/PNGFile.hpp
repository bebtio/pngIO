#pragma once

#include <iostream>

#include "PNGChunk.hpp"
class PNGFile
{

public:
    PNGFile( std::string filename )
    {
        readPNGFile(filename);
    }
    
    
    const std::vector<PNGChunk>& getChunks() { return( _chunks ); }

private:

    std::vector<uint8_t> _header;
    std::vector<PNGChunk> _chunks;


    void readPNGFile( std::string filename );
};