#include "PNGIOTypesTests.hpp"

#include "PNGIOTypes.hpp"
#include "PNGChunk.hpp"


TEST_F( PNGIOTypesTests, IHDRChunkReadTest )
{
    PNGChunk chunk = readPNGChunk(getTestImagePath(), 8);

    pngIO::IHDRChunk ihdrChunk;
    ihdrChunk.readFromRawPNGChunk(chunk);

    FAIL();
}

// *************************************************** //
//
// Sets up the input dir and output dir variables so I
// can use them in all my tests.
//
// *************************************************** //
void PNGIOTypesTests::SetUp()
{
    _testImagePath = std::filesystem::path(INPUT_DIR) / "testImage.png";
    _inputDir      = INPUT_DIR;
    _outputDir     = OUTPUT_DIR;

    // Create the output directory if it does not exist yet.
    if( !std::filesystem::exists(_outputDir) )
    {
        std::filesystem::create_directories(_outputDir);
    }
}