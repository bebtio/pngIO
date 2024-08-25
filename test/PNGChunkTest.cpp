#include <filesystem>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "PNGChunk.hpp"
#include "PNGIOTypes.hpp"

// *************************************************** //
// Test name: PNGChunkTest.ReadHeaderTest
// 
// 1. Reads the signature of the testImage.png file.
// 2. Checks that the signature is exactly eight bytes
// 3. then compares the bytes to the png signature: 137 80 78 71 13 10 26 10
//
// If either steps 2. or 3. fails, the test fails.
// *************************************************** //
TEST( PNGChunkTest, ReadHeaderTest )
{
    std::filesystem::path p(INPUT_DIR);
    p /= "testImage.png";    

    std::vector<std::byte> header = readPNGSignature( p.string() );

    // The header should contain exactly 8 bytes.
    ASSERT_EQ( header.size(), 8 );

    // Compare each of the 8 bytes to the PNG file signature.
    for( size_t i = 0; i < pngIO::signature.size(); i++ )
    {
        ASSERT_EQ( static_cast<uint8_t>(header[i]), pngIO::signature[i] );
    }
}

// *************************************************** //
// Test name PNGChunkTest.ReadChunkTest
//
// Constructs a vector of PNGChunks based on a known png, testImage.png.
// Reads in reads in the testImage.png file and compares the contents of each chunk to the
// constructed vector of PNGChunks.
// *************************************************** //
TEST( PNGChunkTest, ReadChunkTest )
{

    std::vector<PNGChunk> chunks;

    FAIL();
}