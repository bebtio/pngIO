#include "PNGFile.hpp"
#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"

/// ********************************************************** ///
/// \name load
///
/// \brief Loads a png from a file.
///
/// \param filename : std::string - name of the file to load.
///
/// \return bool - true on success, false on fail.
/// ********************************************************** ///
bool
PNGFile::load( const std::string &filename )
{
    bool readSuccess(true);
    bool doneReading(false);
    bool isPng(hasPNGSignature(filename));
    size_t offset(pngIO::signature.size());

    std::vector<PNGChunk> chunks;

    // Keep reading chunks, incrementing the offset by the size of each chunk
    // until we reach the IEND chunk which is 0x49454e44 in hex.
    while( doneReading != true && isPng )
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

    return( readSuccess );
}

/// ********************************************************** ///
/// \name write
///
/// \brief Writes a PNGFile object from to a file.
///
/// \param filename : std::string - name of the file to write to.
///
/// \return bool - true on success, false on fail.
/// ********************************************************** ///
bool
PNGFile::write( const std::string &filename )
{
    bool fileWritten(false);

    return(fileWritten);
}