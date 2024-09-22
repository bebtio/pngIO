#pragma once

#include <vector>

namespace pngIO 
{

// Helper function to append to the byte buffer using an ostringstream
template<typename T>
void appendToBuffer(std::vector<std::byte>& buffer, const T& value) 
{
    buffer.insert(buffer.end(),
                  reinterpret_cast<const std::byte*>(&value),
                  reinterpret_cast<const std::byte*>(&value) + sizeof(value));
}

}