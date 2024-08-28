#include "PNGChunkTest.hpp"

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
TEST_F( PNGChunkTest, ReadSignatureTest )
{
    std::vector<std::byte> header = readPNGSignature( getTestImagePath().string() );

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
TEST_F( PNGChunkTest, NumChunksTest )
{
    PNGFile png;
    png.load( getTestImagePath().string() );

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
// Test name: PNGChunkTest.ChunksContentsTest
//
// This test compares the contents read out by the xxd tool
// when ran on testImage.png to what the PNGFile class reads in
// from the png file.
//
// We compare the chunks that were read in.
// There should be three chunks, the IHDR, IDAT, and IEND.
//
// The bytes read by the xxd tool are as follows:
// 00000000: 8950 4e47 0d0a 1a0a 0000 000d 4948 4452  .PNG........IHDR
// 00000010: 0000 000a 0000 000a 0802 0000 0002 5058  ..............PX
// 00000020: ea00 0001 4149 4441 5418 1901 3601 c9fe  ....AIDAT...6...
// 00000030: 01ff ffff 0000 0000 0000 0000 0000 0000  ................
// 00000040: 0000 0000 0000 0000 0000 0000 0000 0002  ................
// 00000050: 0000 0000 0000 0000 0000 0000 0000 0000  ................
// 00000060: 0000 0000 0000 0000 0000 0000 0000 0200  ................
// 00000070: 0000 0000 0001 0101 0000 0000 0000 0000  ................
// 00000080: 0000 0000 0101 0100 0000 0000 0002 0000  ................
// 00000090: 0000 0000 ffff ff01 0101 0000 0000 0000  ................
// 000000a0: 0101 01ff ffff 0000 0000 0000 01ff ffff  ................
// 000000b0: 0000 0000 0000 0000 0001 0101 0000 00ff  ................
// 000000c0: ffff 0000 0000 0000 0000 0002 0000 0000  ................
// 000000d0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
// 000000e0: 0000 0000 0000 0000 0000 0200 0000 0000  ................
// 000000f0: 0000 0000 0101 01ff ffff ffff ff01 0101  ................
// 00000100: 0000 0000 0000 0000 0002 0000 0000 0000  ................
// 00000110: 0101 01ff ffff 0000 0000 0000 ffff ff01  ................
// 00000120: 0101 0000 0000 0000 01ff ffff 0000 0000  ................
// 00000130: 0000 0000 0000 0000 0000 0000 0000 0000  ................
// 00000140: 0000 0000 0000 0002 0000 0000 0000 0000  ................
// 00000150: 0000 0000 0000 0000 0000 0000 0000 0000  ................
// 00000160: 0000 0000 0000 8b66 1e0f 7638 8924 0000  .......f..v8.$..
// 00000170: 0000 4945 4e44 ae42 6082                 ..IEND.B`.
//
// The data for each section begins right after the chunk's typeCode and ends
// 4 bytes before the next typeCode. These four bytes before the type code are
// the length of the data field in bytes.
// The structure of this output is described here: http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html
//
// *************************************************** //
TEST_F( PNGChunkTest, ChunksContentsTest )
{
    PNGFile png;
    png.load( getTestImagePath().string() );

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

// *************************************************** //
// Test name: PNGChunkTest.WriteToFileTest
//
// Test procedure.
// 1. Reads in a known PNGChunk (chunk) from testImage.png 
// 2. Writes that same PNGChunk back to a file ("PNGChunkTest_WriteToFileTest_chunk.txt").
// 3. Reads in that new PNGChunk (reReadChunk).
// 4. Compares the original, chunk, to the copy, reReadChunk.
// 5. If their contents are identical, the test passes.
//    Fails otherwise.
// *************************************************** //
TEST_F( PNGChunkTest, WriteToFileTest )
{
    std::filesystem::path output( getOutputDir() / "PNGChunkTest_WriteToFileTest_chunk.txt");

    // Read the first chunk of the PNG file.
    PNGChunk chunk( readPNGChunk(getTestImagePath(), 8) );

    // Check that we completed the write to the file.
    ASSERT_TRUE( writePNGChunk( chunk, output.string() ) ) << "Failed to write file: " << output.string();

    // The the written chunk back in.
    PNGChunk reReadChunk = readPNGChunk( output.string(), 0 );

    // Compare the size in bytes, typecode, and CRC of both chunks to make sure they are the same.
    ASSERT_EQ( chunk.getSizeInBytes(), reReadChunk.getSizeInBytes() );
    ASSERT_EQ( chunk.getLength(),      reReadChunk.getLength()      );
    ASSERT_EQ( chunk.getTypeCode(),    reReadChunk.getTypeCode()    );
    ASSERT_EQ( chunk.getCRC(),         reReadChunk.getCRC()         );

    for( size_t i = 0; i < chunk.getData().size(); i++ )
    {
        ASSERT_EQ( chunk.getData()[i], reReadChunk.getData()[i] );
    }
}

void PNGChunkTest::SetUp()
{
    _testImagePath = std::filesystem::path(INPUT_DIR) / "testImage.png";
    _outputDir     = OUTPUT_DIR;

    // Create the output directory if it does not exist yet.
    if( !std::filesystem::exists(_outputDir) )
    {
        std::filesystem::create_directories(_outputDir);
    }
}

void PNGChunkTest::TearDown()
{

}