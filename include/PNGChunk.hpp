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
struct PNGChunk
{

    PNGChunk(): 
      length(0)
    , typeCode(0)
    , data(0)
    , crc(0)
    {}

    uint32_t length;
    uint32_t typeCode;

    std::vector<std::byte> data;

    uint32_t crc;


    std::string ptoString();
};

PNGChunk 
readPNGChunk( std::string filename, size_t offset, size_t &bytesRead );
