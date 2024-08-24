#include "PNGFile.hpp"
void PNGFile::readPNGFile( std::string filename )
{
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

    this->_chunks = chunks;

    for( std::byte b : headerData )
    {
        this->_header.push_back( static_cast<uint8_t>(b));
    }
}


bool writeToFile( std::string filename )
{
    std::ofstream outputFile( filename, std::ios::binary );
    bool writeSuccess(true);

    if( outputFile.good() )
    {

    }

    outputFile.close();

    return(writeSuccess);

}