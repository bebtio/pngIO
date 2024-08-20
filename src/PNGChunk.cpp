#include "PNGChunk.hpp"

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

        pngFile.read(reinterpret_cast<char*>(&chunk.length), sizeof(chunk.length));
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

    // The size of all the data elements in the chunk minus the start location is the number of bytes read.
    // You can then use this to compute the offset for the next chunk.
    bytesRead = sizeof(chunk.length) + sizeof(chunk.typeCode) + chunk.data.size() * sizeof(std::byte) + sizeof(chunk.crc);

    return( chunk );
}