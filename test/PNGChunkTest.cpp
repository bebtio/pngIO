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

    // Size of each chunk in bytes.
    size_t IHDRSize(25);
    size_t IDATSize(333);
    size_t IENDSize(12);
    size_t sharedSize(12);

    // Compare the chunks size in bytes to the expected size.
    ASSERT_EQ( chunks[0].getSizeInBytes(), IHDRSize );
    ASSERT_EQ( chunks[1].getSizeInBytes(), IDATSize );
    ASSERT_EQ( chunks[2].getSizeInBytes(), IENDSize );

    // Now compare the data elements length to the expected value.
    ASSERT_EQ( chunks[0].getLength(), IHDRSize - sharedSize );
    ASSERT_EQ( chunks[1].getLength(), IDATSize - sharedSize );
    ASSERT_EQ( chunks[2].getLength(), IENDSize - sharedSize );

    // Compare the stored length variable to the actuall length of the data.
    ASSERT_EQ( chunks[0].getLength(), chunks[0].getData().size() );
    ASSERT_EQ( chunks[1].getLength(), chunks[1].getData().size() );
    ASSERT_EQ( chunks[2].getLength(), chunks[2].getData().size() );
}

// *************************************************** //
// *************************************************** //
TEST( PNGChunkTest, ChunksContentsTest )
{

    std::filesystem::path p(INPUT_DIR);
    p /= "testImage.png";

    PNGFile png;
    png.load( p.string() );

    std::vector<PNGChunk> chunks = png.getChunks();    

    // Chunks read from the png file.
    PNGChunk IHDRChunk = chunks.at(0);
    PNGChunk IDATChunk = chunks.at(1);
    PNGChunk IENDChunk = chunks.at(2);

    // Chunk data read using xxd linux tool.
    std::array<uint8_t,13> IHDRdata = {
                                      0x00, 0x00, 0x00, 0x0a, 
                                      0x00, 0x00, 0x00, 0x0a, 
                                      0x08, 0x02, 0x00,0x00, 
                                      0x00
                                    };

    std::array<uint8_t,321> IDATdata = {
                                          0x18, 0x19, 0x01, 0x36, 0x01, 0xC9, 0xFE, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x01,
                                          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                                          0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x66, 0x1E,
                                          0x0F
                                        };
    
    // Compare the IHDR data from the png file to the expected value.
    for( size_t i = 0; i < IHDRdata.size(); i++ )
    {
        ASSERT_EQ( static_cast<uint8_t>(IHDRChunk.getData().at(i)), IHDRdata[i] );
    }

    // Compare the IDAT data from the png file to the expected value.
    for( size_t i = 0; i < IDATdata.size(); i++ )
    {
        ASSERT_EQ( static_cast<uint8_t>(IDATChunk.getData().at(i)), IDATdata[i] );
    }

    // IEND has no data so we just need to check that the data vector size is 0 here.
    ASSERT_EQ( IENDChunk.getData().size(), 0 );
}