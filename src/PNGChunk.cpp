#include "PNGChunk.hpp"

#include "PNGIOTypes.hpp"

#include <algorithm>
#include <iostream>
#include <string>


/// ************************************************************************** ///
/// \name readPNGSignature
///
/// \brief Returns true if the file read in has a valid png signature. Otherwise
///        returns false. 
///
/// \param[in] filename - a string containing the filename to check for a valid
///                       png signature.
///
/// \return bool
/// ************************************************************************** ///
bool
hasPNGSignature( const std::string &filename )
{
    bool sigFound(false);

    std::vector<uint8_t> sigData(pngIO::signature.size());

    std::ifstream pngFile( filename, std::ios::binary );
    
    if( pngFile.is_open() )
    {
        pngFile.read(reinterpret_cast<char*>(sigData.data()), pngIO::signature.size());
    }

    pngFile.close();

    // Compare what we read in to what we know is the png signature.
    if( std::equal( sigData.begin(), sigData.end(), pngIO::signature.begin() ) )
    {
        sigFound = true;
    }
    
    return(sigFound);
}

/// ************************************************************************** ///
/// \name writePNGSignature
///
/// \brief Writes the png signature to a file. Returns true on success, false if failure.
///
/// \param[in] filename - a string containing the filename to write png signature to.
///
/// \return bool
/// ************************************************************************** ///
bool writePNGSignature( const std::string &filename )
{
    bool writeSuccess(false);
    std::ofstream pngFile( filename, std::ios::binary );

    if( pngFile.is_open() )
    {
        pngFile.write( reinterpret_cast<const char*>(pngIO::signature.data()), pngIO::signature.size() );

        writeSuccess = true;
    }

    pngFile.close();

    return(writeSuccess);
}

/// ************************************************************************** ///
/// \brief Reads a png file's chunk data at location offset.
///        Returns the number of bytes 
/// Because PNG's are stored in network byte order, we should call ntoh[ls]
/// as we read in the data to get the correct endianess for our machine.
/// will return a chunk of size bytes 0 on error.
///
/// \param[in]  filename  - name of the png file to read in.
/// \param[in]  offset    - how many bytes into the file to read in the png chunkd.
///
/// \return PNGChunk
/// ************************************************************************** ///
PNGChunk 
readPNGChunk( const std::string &filename, size_t offset )
{

    PNGChunk chunk;

    // open the file for reading.
    std::ifstream pngFile( filename, std::ios::binary );
    
    uint32_t               length(0);
    uint32_t               typeCode(0);
    std::vector<std::byte> data(0);
    uint32_t               crc(0);

    if( pngFile.good() )
    {
        // Skip the first offset bytes to get to the chunk we want.
        pngFile.ignore(offset);

        // Read the length element, this will tell how many bytes to read from the data portion of the chunk.
        pngFile.read(reinterpret_cast<char*>(&length), sizeof(length));
        length = ntohl(length);
        chunk.setLength(length);

        // Next read the typeCode, this will tell us what kind of data this chunk contains.
        pngFile.read(reinterpret_cast<char*>(&typeCode), sizeof(typeCode));
        typeCode = ntohl(typeCode);
        chunk.setTypeCode(typeCode);

        // We only continue the read if the type code is valid!
        if( chunk.isValid() ) 
        {
            // Resize the data to the length read in.
            data.resize(length);

            // Loop over the bytes and read them in.
            pngFile.read(reinterpret_cast<char*>(&data[0]), length);
            chunk.setData(data);

            // Lastly read in the CRC. We won't do error checking on the chunks quite yet.
            pngFile.read(reinterpret_cast<char*>(&crc), sizeof(crc));
            crc = ntohl(crc);
            chunk.setCRC(crc);

            std::cout << __FILE__ << ":" << __LINE__ << ":";
            std::cout << "ADD PNG CRC CHECK HERE" << std::endl;
        }
        else
        {
            // If the type code is invalid reset the member we have 
            // set previously.
            chunk.setLength(0);
            chunk.setTypeCode(0);
        }
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

        std::cout << __FILE__ << "::" << __LINE__ << ": ADD CRC GENERATION HERE" << std::endl;
        chunkFile.write(reinterpret_cast<char*>(&crc), sizeof(crc));

        writeSuccess = true;
    }

    chunkFile.close();

    return(writeSuccess);
}

size_t
PNGChunk::getSizeInBytes() const
{
    size_t chunkSize(0);

    // The size of all the data elements in the chunk is the number of bytes read.
    // You can then use this to compute the offset for the next chunk.
    chunkSize = sizeof(this->_length) + sizeof(this->_typeCode) + this->_data.size() * sizeof(std::byte) + sizeof(this->_crc);

    return(chunkSize);
}

bool
PNGChunk::isValid() const
{
    bool isValid(false);
    
    switch (_typeCode)
    {
        case static_cast<uint32_t>(pngIO::TypeCodes::IHDR):
        case static_cast<uint32_t>(pngIO::TypeCodes::PLTE):
        case static_cast<uint32_t>(pngIO::TypeCodes::IDAT):
        case static_cast<uint32_t>(pngIO::TypeCodes::IEND):
        case static_cast<uint32_t>(pngIO::TypeCodes::cHRM):
        case static_cast<uint32_t>(pngIO::TypeCodes::gAMA):
        case static_cast<uint32_t>(pngIO::TypeCodes::iCCP):
        case static_cast<uint32_t>(pngIO::TypeCodes::sBIT):
        case static_cast<uint32_t>(pngIO::TypeCodes::sRGB):
        case static_cast<uint32_t>(pngIO::TypeCodes::bKGD):
        case static_cast<uint32_t>(pngIO::TypeCodes::hIST):
        case static_cast<uint32_t>(pngIO::TypeCodes::tRNS):
        case static_cast<uint32_t>(pngIO::TypeCodes::pHYs):
        case static_cast<uint32_t>(pngIO::TypeCodes::sPLT):
        case static_cast<uint32_t>(pngIO::TypeCodes::tIME):
        case static_cast<uint32_t>(pngIO::TypeCodes::iTXt):
        case static_cast<uint32_t>(pngIO::TypeCodes::tEXt):
        case static_cast<uint32_t>(pngIO::TypeCodes::zTXt):
            return true;
        default:
            return false;
    }
    return(isValid);
}

std::string PNGChunk::toString() const
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
