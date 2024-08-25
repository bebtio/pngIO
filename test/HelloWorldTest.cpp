#include <gtest/gtest.h>
#include <string>

#include "PNGFile.hpp"

TEST( HelloWorldTest, FirstTest )
{
    std::string str("Hello World!");

    ASSERT_EQ(str, "Hello World!");
}

TEST( PNGIOTest, ConstructorTest )
{

    PNGFile png("../testImage.png");

    std::vector<PNGChunk> chunks = png.getChunks();

    ASSERT_EQ( chunks.size(), 3 );

}