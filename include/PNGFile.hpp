#pragma once

#include <iostream>
#include <optional>

#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"
class PNGFile
{

public:
    PNGFile() {}
    
    bool load( const std::string &filename );
    bool write( const std::string &filename );
    void clear();

    const std::vector<PNGChunk>& getChunks() { return( _chunks ); } 

    std::optional<PNGChunk> 
    getPNGChunk( pngIO::TypeCodes type ); 

    bool 
    setPNGChunk( const PNGChunk &chunk );

private:

    std::vector<PNGChunk> _chunks;

};