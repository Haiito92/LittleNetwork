#pragma once
#include <type_traits>
#include <vector>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value);

    template <typename T> requires std::is_arithmetic_v<T>
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset);
    
}

#include "Serialization.inl"
