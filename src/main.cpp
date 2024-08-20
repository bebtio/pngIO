#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <arpa/inet.h>

#include "PNGChunk.hpp"



struct IHDRChunk
{
    IHDRCHunk( const PNGChunk &chunk );

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

PNGChunk 
readPNGChunk( std::string filename, size_t offset, size_t &bytesRead );

IHDRChunk
readIHDRChunkHeader( std::string filename );

int main(int argc, char* argv[])
{
    std::cout << "Hello world" << std::endl;

    std::vector<std::byte> headerData = readPNGHeader("../testImage.png");

    std::cout << "header:    ";
    for( const std::byte &b : headerData )
    {
        std::cout << std::to_integer<int>(b) << " ";

    } 
    std::cout << std::endl;

    size_t bytesRead(0);
    PNGChunk chunk = readPNGChunk( "../testImage.png", headerData.size(), bytesRead );

    std::cout << chunk << std::endl;


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




// ************************************************************************** //
// filename - file to read data from
// offset - number of bytes to skip before starting reading.
// bytesRead - return number of bytes this chunk takes up.
// ************************************************************************** //
PNGChunk 
readPNGChunk( std::string filename, size_t offset, size_t &bytesRead )
{

    PNGChunk chunk;
    size_t startLoc(offset);

    std::ifstream pngFile( filename, std::ios::binary );

    if( pngFile.good() )
    {
        pngFile.ignore(offset);

        pngFile.read(reinterpret_cast<char*>(&chunk.length), sizeof(uint32_t));
        chunk.length = ntohl(chunk.length);

        pngFile.read(reinterpret_cast<char*>(&chunk.typeCode), sizeof(chunk.typeCode));
        chunk.typeCode = ntohl(chunk.typeCode);

        chunk.data.resize(chunk.length);

        for( size_t i; i < chunk.length; i++ )
        {
            pngFile.read(reinterpret_cast<char*>(&chunk.data[i]), 1);
        }
    
        pngFile.read(reinterpret_cast<char*>(&chunk.crc), sizeof(chunk.crc));
    }


    pngFile.close();

    return( chunk );
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