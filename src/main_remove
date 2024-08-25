#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <arpa/inet.h>

#include "PNGFile.hpp"


struct IHDRChunk
{

    uint32_t width;
    uint32_t height;
    uint8_t  bitDepth;
    uint8_t  colorType;
    uint8_t  compressionMethod;
    uint8_t  filterMethod;
    uint8_t  interlaceMethod;
};


IHDRChunk
readIHDRChunkHeader( std::string filename );

int main(int argc, char* argv[])
{
    std::cout << "Hello world" << std::endl;

    PNGFile png( "../testImage.png" );

    std::vector<PNGChunk> chunks = png.getChunks();
    std::cout << "Complete" << std::endl;
    std::cout << "Chunks read: " << chunks.size() << std::endl << std::endl;

    int chunkCount(0);
    for( PNGChunk &c : chunks )
    {
        std::cout << "Chunk: " << chunkCount << std::endl;
        chunkCount++;
        std::cout << c.toString() << std::endl;
    }

    return(0);
}


IHDRChunk
readIHDRChunkHeader( std::string filename )
{
    std::ifstream pngFile( filename );

    IHDRChunk chunk;

    if( pngFile.good() )
    {
        pngFile.ignore(8);
        pngFile >> chunk.width;
        pngFile >> chunk.height;
        pngFile >> chunk.bitDepth;
        pngFile >> chunk.colorType;
        pngFile >> chunk.compressionMethod;
        pngFile >> chunk.filterMethod;
        pngFile >> chunk.interlaceMethod;
    }

    return( chunk );
}