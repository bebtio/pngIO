#include <variant>
#include <vector>
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

// Define vector variant type
using PixelVector = std::variant<
    std::monostate,
    std::vector<GrayscalePixel8>,
    std::vector<GrayscalePixel16>,
    std::vector<GrayscalePixelA8>,
    std::vector<GrayscalePixelA16>,
    std::vector<RGBPixel8>,
    std::vector<RGBPixel16>,
    std::vector<RGBAPixel8>,
    std::vector<RGBAPixel16>
>;

}