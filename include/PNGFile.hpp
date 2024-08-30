#pragma once

#include <iostream>

#include "PNGChunk.hpp"
class PNGFile
{

public:
    PNGFile() {}
    
    bool load( const std::string &filename );
    bool write( const std::string &filename );
    void clear();

    const std::vector<PNGChunk>& getChunks() { return( _chunks ); } 

private:

    std::vector<PNGChunk> _chunks;

};