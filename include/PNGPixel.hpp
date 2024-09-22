#include <variant>
#include <cstdint>

namespace pngIO
{


// Define pixel structs
struct GrayscalePixel8   { uint8_t  value;      };
struct GrayscalePixel16  { uint16_t value;      };
struct GrayscalePixelA8  { uint8_t  value, a;   };
struct GrayscalePixelA16 { uint16_t value, a;   };
struct RGBPixel8         { uint8_t  r, g, b;    };
struct RGBPixel16        { uint16_t r, g, b;    };
struct RGBAPixel8        { uint8_t  r, g, b, a; };
struct RGBAPixel16       { uint16_t r, g, b, a; };

// Define variant type
using Pixel = std::variant<
    GrayscalePixel8,
    GrayscalePixel16,
    GrayscalePixelA8,
    GrayscalePixelA16,
    RGBPixel8,
    RGBPixel16,
    RGBAPixel8,
    RGBAPixel16
>;

}