#include "PNGChunk.hpp"

// ************************************************************************** //
//
// filename - file to read data from
// offset - number of bytes to skip before starting reading.
// bytesRead - return number of bytes this chunk takes up.
// 
// Becuase PNG's are stored in network byte order, we should call ntoh[ls]
// as we reada in the data to get the correct endianess for our machine.
//
// ************************************************************************** //
PNGChunk 
readPNGChunk( std::string filename, size_t offset, size_t &bytesRead )
{

    PNGChunk chunk;

    // open the file for reading.
    std::ifstream pngFile( filename, std::ios::binary );

    if( pngFile.good() )
    {
        // Skip the first offset bytes to get to the chunk we want.
        pngFile.ignore(offset);

        // Read the length element, this will tell how many bytes to read from the data portion of the chunk.
        pngFile.read(reinterpret_cast<char*>(&chunk.length), sizeof(chunk.length));
        chunk.length = ntohl(chunk.length);

        // Next read the typeCode, this will tell us what kind of data this chunk contains.
        pngFile.read(reinterpret_cast<char*>(&chunk.typeCode), sizeof(chunk.typeCode));
        chunk.typeCode = ntohl(chunk.typeCode);

        // Resize the data to the length read in.
        chunk.data.resize(chunk.length);

        // Loop over the bytes and read them in.
        for( size_t i; i < chunk.length; i++ )
        {
            pngFile.read(reinterpret_cast<char*>(&chunk.data[i]), 1);
        }
    
        // Lastly read in the CRC. We won't do error checking on the chunks quite yet.
        pngFile.read(reinterpret_cast<char*>(&chunk.crc), sizeof(chunk.crc));
    }


    pngFile.close();

    // The size of all the data elements in the chunk is the number of bytes read.
    // You can then use this to compute the offset for the next chunk.
    bytesRead = sizeof(chunk.length) + sizeof(chunk.typeCode) + chunk.data.size() * sizeof(std::byte) + sizeof(chunk.crc);

    return( chunk );
}