#include "PNGFile.hpp"
#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"
#include <cstdint>
#include <optional>

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
    bool readSuccess = hasPNGSignature(filename);
    size_t offset = pngIO::signature.size();

    // Continue reading until the IEND chunk is found or an error occurs.
    while( readSuccess )
    {
        PNGChunk chunk = readPNGChunk(filename, offset);

        if( !chunk.isValid() )
        {
            // If an invalid chunk is found, clear the chunks and exit the loop.
            readSuccess = false;
            this->_chunks.clear();
            break;
        }

        // Add the chunk and update the offset.
        offset += chunk.getSizeInBytes();
        this->_chunks.push_back(chunk);

        // Check if we've reached the IEND chunk.
        if( chunk.getTypeCode() == static_cast<uint32_t>(pngIO::TypeCodes::IEND) )
        {
            break;
        }
    }

    return readSuccess;
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
    bool fileWritten(writePNGSignature(filename));

    if( fileWritten )
    {
        for( PNGChunk &chunk : _chunks )
        {
            // Re-generate the CRC in case the data has been modified.
            chunk.setCRC();
            if( !writePNGChunk( chunk, filename ) )
            {
                fileWritten = false;
                break;
            }
        }
    }

    return(fileWritten);
}

void PNGFile::clear()
{
    _chunks.clear();
}

std::optional<PNGChunk>
PNGFile::getPNGChunk( pngIO::TypeCodes type )
{
    for( const PNGChunk &chunk : this->_chunks )
    {
        if( chunk.getTypeCode() == static_cast<uint32_t>(type) )
        {
            return( std::optional(chunk) );
        }
    }

    return( std::nullopt );
}

bool
PNGFile::setPNGChunk( const PNGChunk &chunk )
{
    if( !chunk.isValid() )
    {
        return( false );
    }

    for( PNGChunk &chunkRef: this->_chunks )
    {
        if( chunk.getTypeCode() == chunkRef.getTypeCode() )
        {
            chunkRef = chunk;
            return(true);
        }
    }

    this->_chunks.push_back(chunk);
    return(true);
}