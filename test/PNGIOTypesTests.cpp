#include "PNGIOTypesTests.hpp"

#include "PNGIOTypes.hpp"
#include "PNGChunk.hpp"

// *************************************************** //
// Test name: PNGIOTypesTests.IHDRChunkReadTest
// Reads in a IHDR chunk from the testImage.png
// and constructs a IHDRChunk from it.
//
// We then compare the known values of that chunk to 
// what was read in. If any of the IHDR elements do not match
// what is expected, the test fails.
// *************************************************** //
TEST_F( PNGIOTypesTests, IHDRChunkReadTest )
{
    PNGChunk chunk = readPNGChunk(getTestImagePath(), 8);

    pngIO::IHDRChunk ihdrChunk;
    ihdrChunk.readFromRawPNGChunk(chunk);

    ASSERT_EQ( ihdrChunk.getTypeCode(),          pngIO::TypeCodes::IHDR );
    ASSERT_EQ( ihdrChunk.getLength(),            13                     );
    ASSERT_EQ( ihdrChunk.getWidth(),             10                     );
    ASSERT_EQ( ihdrChunk.getHeight(),            10                     );
    ASSERT_EQ( ihdrChunk.getBitDepth(),          pngIO::BitDepth::eight );
    ASSERT_EQ( ihdrChunk.getColorType(),         pngIO::ColorType::rgb  );
    ASSERT_EQ( ihdrChunk.getCompressionMethod(), 0                      );
    ASSERT_EQ( ihdrChunk.getFilterMethod(),      0                      );
    ASSERT_EQ( ihdrChunk.getInterlaceMethod(),   0                      );
}

// *************************************************** //
// Test name: PNGIOTypesTests.IHDRChunkWriteTest
//
// This tests the ability for IHDRChunk to write a
// a PNGChunk with the correct values.
//
// We create a IHDRChunk custom values.
// We then write that IHDRChunk to a PNGChunk object.
// We then take the PNGChunk object and construct the
// newIHDRChunk from that.
//
// Finally we take our originalIHDRChunk and compare the 
// elements to the newIHDRChunk.
//
// If the elements are all equal then the test passes.
// *************************************************** //
TEST_F( PNGIOTypesTests, IHDRChunkWriteTest )
{
    pngIO::IHDRChunk originalIHDRChunk;
    pngIO::IHDRChunk newIHDRChunk;
    PNGChunk chunk;

    // Create a IHDRChunk with some.
    originalIHDRChunk.setTypeCode( pngIO::TypeCodes::IHDR );
    originalIHDRChunk.setLength( 13 );
    originalIHDRChunk.setWidth( 100 );
    originalIHDRChunk.setWidth( 150 );
    originalIHDRChunk.setBitDepth( pngIO::BitDepth::one );
    originalIHDRChunk.setColorType( pngIO::ColorType::grayScale );
    originalIHDRChunk.setCompressionMethod( 0 );
    originalIHDRChunk.setFilterMethod( 0 );
    originalIHDRChunk.setInterlaceMethod( 0 );

    // Create a raw chunk with this data in it.
    ASSERT_TRUE( originalIHDRChunk.writeRawPNGChunk(chunk) );

    // Create a new IHDRChunk using the raw chunk as input
    ASSERT_TRUE( newIHDRChunk.readFromRawPNGChunk( chunk ) );
    
    // Compare the original to the newly created IHDRChunk and esure they are the same.
    ASSERT_EQ( originalIHDRChunk.getTypeCode(),          newIHDRChunk.getTypeCode()          );
    ASSERT_EQ( originalIHDRChunk.getLength(),            newIHDRChunk.getLength()            );
    ASSERT_EQ( originalIHDRChunk.getWidth(),             newIHDRChunk.getWidth()             );
    ASSERT_EQ( originalIHDRChunk.getHeight(),            newIHDRChunk.getHeight()            );
    ASSERT_EQ( originalIHDRChunk.getBitDepth(),          newIHDRChunk.getBitDepth()          );
    ASSERT_EQ( originalIHDRChunk.getColorType(),         newIHDRChunk.getColorType()         );
    ASSERT_EQ( originalIHDRChunk.getCompressionMethod(), newIHDRChunk.getCompressionMethod() );
    ASSERT_EQ( originalIHDRChunk.getFilterMethod(),      newIHDRChunk.getFilterMethod()      );
    ASSERT_EQ( originalIHDRChunk.getInterlaceMethod(),   newIHDRChunk.getInterlaceMethod()   );
}