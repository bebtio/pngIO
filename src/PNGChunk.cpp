#include "PNGChunk.hpp"
#include <iostream>
#include <string>


// ************************************************************************** //
//
//
// ************************************************************************** //
std::vector<std::byte>
readPNGSignature( const std::string &filename )
{
    std::vector<std::byte> sigData;
    char byte;
    std::ifstream pngFile( filename, std::ios::binary );
    
    const size_t pngFileSignatureSize(8);
    
    if( pngFile.good() )
    {
        for( size_t i = 0; i < pngFileSignatureSize; i++ )
        {
            pngFile.read(&byte, 1);
            sigData.push_back(std::byte(byte));
        }
    }

    pngFile.close();

    return( sigData );
}

// ************************************************************************** //
// \brief Reads a png file's chunk data at location offset.
//        Returns the number of bytes 
// Because PNG's are stored in network byte order, we should call ntoh[ls]
// as we read in the data to get the correct endianess for our machine.
// will return a chunk of size bytes 0 on error.
//
// \param[in]  filename  - name of the png file to read in.
// \param[in]  offset    - how many bytes into the file to read in the png chunkd.
//
// \return PNGChunk
// ************************************************************************** //
PNGChunk 
readPNGChunk( const std::string &filename, size_t offset )
{

    PNGChunk chunk;

    // open the file for reading.
    std::ifstream pngFile( filename, std::ios::binary );
    
    uint32_t length(0);
    uint32_t typeCode(0);
    std::vector<std::byte> data(0);
    uint32_t crc(0);

    if( pngFile.good() )
    {
        // Skip the first offset bytes to get to the chunk we want.
        pngFile.ignore(offset);

        // Read the length element, this will tell how many bytes to read from the data portion of the chunk.
        pngFile.read(reinterpret_cast<char*>(&length), sizeof(length));
        chunk.setLength(ntohl(length));

        // Next read the typeCode, this will tell us what kind of data this chunk contains.
        pngFile.read(reinterpret_cast<char*>(&typeCode), sizeof(typeCode));
        chunk.setTypeCode(ntohl(typeCode));

        // Resize the data to the length read in.
        data.resize(chunk.getLength());

        // Loop over the bytes and read them in.
        pngFile.read(reinterpret_cast<char*>(&data[0]), chunk.getLength());
        chunk.setData(data);
    
        // Lastly read in the CRC. We won't do error checking on the chunks quite yet.
        pngFile.read(reinterpret_cast<char*>(&crc), sizeof(crc));
        chunk.setCRC(ntohl(crc));

        std::cout << __FILE__ << ":" << __LINE__ << ":";
        std::cout << "ADD PNG CRC CHECK HERE" << std::endl;
    }

    pngFile.close();

    return( chunk );
}

bool
writePNGChunk( const PNGChunk &chunk, const std::string &filename )
{
    bool writeSuccess(false);

    std::ofstream chunkFile( filename, std::ios::binary | std::ios::app );

    uint32_t length             = htonl(chunk.getLength());  // Convert to network byte order
    uint32_t typeCode           = htonl(chunk.getTypeCode()); // Convert to network byte order
    std::vector<std::byte> data = chunk.getData();
    uint32_t crc                = htonl(chunk.getCRC()); // Convert to network byte order

    if (chunkFile)
    {
        chunkFile.write(reinterpret_cast<char*>(&length), sizeof(length));
        chunkFile.write(reinterpret_cast<char*>(&typeCode), sizeof(typeCode));
        chunkFile.write(reinterpret_cast<char*>(data.data()), data.size());

        std::cout << __FILE__ << "::" << __LINE__ << "ADD CRC GENRATION HERE" << std::endl;
        chunkFile.write(reinterpret_cast<char*>(&crc), sizeof(crc));

        writeSuccess = true;
    }

    chunkFile.close();

    return(writeSuccess);
}

size_t
PNGChunk::getSizeInBytes()
{
    size_t chunkSize(0);

    // The size of all the data elements in the chunk is the number of bytes read.
    // You can then use this to compute the offset for the next chunk.
    chunkSize = sizeof(this->_length) + sizeof(this->_typeCode) + this->_data.size() * sizeof(std::byte) + sizeof(this->_crc);

    return(chunkSize);
}

std::string PNGChunk::toString()
{
    std::stringstream ss;

    ss << "-----------------------------------------------------" << std::endl
       << "Start of Chunk" << std::endl << std::endl;


    ss << "length:   " << this->getLength()   << std::endl;
    ss << "typeCode: " << this->getTypeCode() << std::endl;

    ss << "data: " << std::endl;

    ss << std::hex << std::uppercase << std::setfill('0'); 
    for (size_t i = 0; i < this->getData().size(); i++)
    {

        if( i % 1 == 0 )
        {
            ss << "0x";
            if( i % 16 == 0 )
            {
                ss << std::endl;
            }
        }
        // Cast std::byte to uint32_t and print as hex with 2 digits
        ss << std::setw(2) << static_cast<uint32_t>(this->getData()[i]) << ", ";
    }


    ss << std::dec << std::nouppercase << std::endl;

    ss << "CRC:      " << this->getCRC() << std::endl << std::endl;

    ss << "End of Chunk" << std::endl
       << "-----------------------------------------------------";
    return ss.str();
}
