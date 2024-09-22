#pragma once

#include <filesystem>

#include <gtest/gtest.h>


class PNGTests : public testing::Test
{

public:
    void SetUp()
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

    void TearDown() {};

    std::filesystem::path getTestImagePath() { return( _testImagePath ); }
    std::filesystem::path getInputDir()      { return( _inputDir);       }
    std::filesystem::path getOutputDir()     { return( _outputDir );     }

private:

    std::filesystem::path _testImagePath;
    std::filesystem::path _inputDir;
    std::filesystem::path _outputDir;

};
