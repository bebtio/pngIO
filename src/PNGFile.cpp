#include "PNGFile.hpp"
#include "PNGIOTypes.hpp"
bool
PNGFile::load( const std::string &filename )
{
    bool readSuccess(true);

    std::vector<std::byte> sigData = readPNGSignature(filename);
    std::vector<PNGChunk> chunks;

    std::cout << "signature:    ";

    for( const std::byte &b : sigData )
    {
        std::cout << std::to_integer<int>(b) << " ";

    } 

    std::cout << std::endl;

    size_t offset(sigData.size());
    bool doneReading(false);

    // Keep reading chunks, incrementing the offset by the size of each chunk
    // until we reach the IEND chunk which is 0x49454e44 in hex.
    while( doneReading != true )
    {
        PNGChunk chunk = readPNGChunk( filename, offset );

        offset += chunk.getSizeInBytes();

        chunks.push_back(chunk);

        if( chunk.getTypeCode() == static_cast<uint32_t>(pngIO::TypeCodes::IEND) )
        {
            doneReading = true;
        }
    }

    this->_chunks = chunks;

    for( std::byte b : sigData )
    {
        this->_signature.push_back( static_cast<uint8_t>(b));
    }


    return( readSuccess );
}