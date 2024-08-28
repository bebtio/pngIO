#pragma once

#include <filesystem>

#include <gtest/gtest.h>


class PNGChunkTest : public testing::Test
{

public:
    void SetUp();
    void TearDown();

    std::filesystem::path getTestImagePath() { return( _testImagePath ); }
    std::filesystem::path getOutputDir()     { return( _outputDir );     }

private:

    std::filesystem::path _testImagePath;
    std::filesystem::path _outputDir;

};