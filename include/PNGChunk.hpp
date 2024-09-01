#pragma once

#include "PNGCrc.hpp"

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <arpa/inet.h>

// PNGChunk data.
//
class PNGChunk
{

public:

    PNGChunk(): 
      _length(0)
    , _typeCode(0)
    , _data{0}
    , _crc(0)
    , _crcGen()
    {}

    void clear();

    uint32_t                      getLength()              const { return(_length);            }
    uint32_t                      getTypeCode()            const { return(_typeCode);          }
    const std::vector<std::byte>& getData()                const { return(_data);              }
    uint32_t                      getCRC()                 const { return(_crc);               }

    void setLength  ( uint32_t length )                    { this->_length   = length;   }
    void setTypeCode( uint32_t typeCode )                  { this->_typeCode = typeCode; }
    void setData    ( const std::vector<std::byte> &data ) { this->_data     = data;     }
    void setCRC     ( uint32_t crc )                       { this->_crc      = crc;      }

    uint32_t generateCRC(); 
    size_t getSizeInBytes() const;

    bool isValid() const;

    std::string toString() const;

private:
    uint32_t               _length;
    uint32_t               _typeCode;
    std::vector<std::byte> _data;
    uint32_t               _crc;

    PNGCrc _crcGen;

};

bool
hasPNGSignature( const std::string &filename );

bool
writePNGSignature( const std::string &filename );
PNGChunk 
readPNGChunk( const std::string &filename, size_t offset );

bool
writePNGChunk( const PNGChunk &chunk, const std::string &filename );