#include "PNGPixelTests.hpp"

#include "PNGPixel.hpp"

TEST_F( PNGPixelTests, DummyTest )
{
    pngIO::PixelVector pixels;

    pixels = std::vector<pngIO::RGBPixel16>(25, {0,0,0});

    auto& vec = std::get<std::vector<pngIO::RGBPixel16>>(pixels); 

   int i = 0; 
    for( auto& p : vec )
    {
        p.r = i;
        p.g = i;
        p.b = i;

        std::cout << p.r << " " << p.g << " " << p.b << std::endl;

        i++;
    }

    pixels = std::vector<pngIO::RGBPixel8>(10,{0,0,0});

    FAIL();

}