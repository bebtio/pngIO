#include "PNGPixelTests.hpp"

#include "PNGPixel.hpp"

TEST_F( PNGPixelTests, DummyTest )
{
    pngIO::PixelVector pixels;

    pixels = std::vector<pngIO::RGBPixel16>(25, {0,0,0});

    for( const auto& p : std::get<std::vector<pngIO::RGBPixel16>>(pixels) )
    {
        std::cout << p.r << " " << p.g << " " << p.b << std::endl;
    }

    FAIL();

}