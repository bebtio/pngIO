#pragma once

#include <iostream>

#include "PNGChunk.hpp"
class PNGFile
{

public:
    PNGFile() {}
    
    bool load( const std::string &filename );
    
    const std::vector<PNGChunk>& getChunks() { return( _chunks ); } 

private:

    std::vector<uint8_t> _signature;
    std::vector<PNGChunk> _chunks;

};