#pragma once

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
    {}

    void clear();

    uint32_t                      getLength()              { return(_length);            }
    uint32_t                      getTypeCode()            { return(_typeCode);          }
    const std::vector<std::byte>& getData()                { return(_data);              }
    uint32_t                      getCRC()                 { return(_crc);               }

    void setLength  ( uint32_t length )                    { this->_length   = length;   }
    void setTypeCode( uint32_t typeCode )                  { this->_typeCode = typeCode; }
    void setData    ( const std::vector<std::byte> &data ) { this->_data     = data;     }
    void setCRC     ( uint32_t crc )                       { this->_crc      = crc;      }

    size_t getSizeInBytes();

    std::string toString();

private:
    uint32_t               _length;
    uint32_t               _typeCode;
    std::vector<std::byte> _data;
    uint32_t               _crc;

};

std::vector<std::byte> 
readPNGSignature( const std::string &filename );

PNGChunk 
readPNGChunk( const std::string &filename, size_t offset );
