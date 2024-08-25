#include <filesystem>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "PNGFile.hpp"
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
TEST( PNGChunkTest, ReadSignatureTest )
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
// Test name: PNGChunkTest.NumChunksTest
//
// Test the testImage.png has exactly 3 chunks.
// They are the IHDR, IDAT, and IEND chunks
// with sizes in bytes of 25, 333, adn 12 respectively.
// Their data lengths are: 13, 321, and 0 respectively.
// 
// Each chunk contains the same 12 bytes: 4 for the type code,
// 4 for the data length, and 4 for the CRC.
// If you subtract the 12 bytes from the sizes in bytes, you just
// get the data lengths, which is the only thing that varies between chunks.
//
// We will compare both chunk sizes and their data members length.
//
// These data were acquired by inspecting the file with the
// linux xxd tool.
//
// If the chunk size or data length vary from the inspected values
// this test fails.
// *************************************************** //
TEST( PNGChunkTest, NumChunksTest )
{
    std::filesystem::path p(INPUT_DIR);
    p /= "testImage.png";

    PNGFile png;
    png.load( p.string() );

    std::vector<PNGChunk> chunks = png.getChunks();    
    
    // Compare the number of chunks to the expected number.
    ASSERT_EQ( chunks.size(), 3 );

    // Compare the chunks size in bytes to the expected size.
    ASSERT_EQ( chunks[0].getSizeInBytes(), 25  );
    ASSERT_EQ( chunks[1].getSizeInBytes(), 333 );
    ASSERT_EQ( chunks[2].getSizeInBytes(), 12  );

    // Now compare the data elements length to the expected value.
    ASSERT_EQ( chunks[0].getLength(), 25  - 12 );
    ASSERT_EQ( chunks[1].getLength(), 333 - 12 );
    ASSERT_EQ( chunks[2].getLength(), 12  - 12 );

    // Compare the stored length variable to the actuall length of the data.
    ASSERT_EQ( chunks[0].getLength(), chunks[0].getData().size() );
    ASSERT_EQ( chunks[1].getLength(), chunks[1].getData().size() );
    ASSERT_EQ( chunks[2].getLength(), chunks[2].getData().size() );
}

// *************************************************** //
// *************************************************** //
TEST( PNGChunkTest, IHDRChunkSizeTest )
{

    std::filesystem::path p(INPUT_DIR);
    p /= "testImage.png";

    PNGFile png;
    png.load( p.string() );

    std::vector<PNGChunk> chunks = png.getChunks();    

    FAIL();
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