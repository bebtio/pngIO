#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <arpa/inet.h>

#include "PNGChunk.hpp"



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

std::vector<std::byte> 
readPNGHeader( std::string filename );



IHDRChunk
readIHDRChunkHeader( std::string filename );

int main(int argc, char* argv[])
{
    std::cout << "Hello world" << std::endl;

    std::vector<std::byte> headerData = readPNGHeader("../testImage.png");
    std::vector<PNGChunk> chunks;

    std::cout << "header:    ";
    for( const std::byte &b : headerData )
    {
        std::cout << std::to_integer<int>(b) << " ";

    } 
    std::cout << std::endl;

    size_t bytesRead(0);
    size_t offset(headerData.size());
    bool doneReading(false);

    // Keep reading chunks, incrementing the offset by the size of each chunk
    // until we reach the IEND chunk which is 0x49454e44 in hex.
    while( doneReading != true )
    {
        PNGChunk chunk = readPNGChunk( "../testImage.png", offset, bytesRead );

        offset += bytesRead;

        chunks.push_back(chunk);

        if( chunk.typeCode == 0x49454e44 )
        {
            doneReading = true;
        }
    }

    std::cout << "Complete" << std::endl;
    std::cout << "Chunks read: " << chunks.size() << std::endl << std::endl;

    int chunkCount(0);
    for( PNGChunk &c : chunks )
    {
        std::cout << "Chunk: " << chunkCount << std::endl;
        chunkCount++;
        std::cout << c.pngChunkToString() << std::endl;
    }

    return(0);
}

std::vector<std::byte>
readPNGHeader( std::string filename )
{
    std::vector<std::byte> headerData;
    char byte;
    std::ifstream pngFile( filename, std::ios::binary );
    
    const size_t pngFileSignatureSize(8);
    
    if( pngFile.good() )
    {
        for( size_t i = 0; i < pngFileSignatureSize; i++ )
        {
            pngFile.read(&byte, 1);
            headerData.push_back(std::byte(byte));
        }
    }

    pngFile.close();

    return( headerData );
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