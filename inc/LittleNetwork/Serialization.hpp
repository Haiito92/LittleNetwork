#pragma once
#include <type_traits>
#include <vector>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    template <typename T> requires std::is_arithmetic<T>::value
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value);

    template <typename T> requires std::is_arithmetic<T>::value
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset);
}

#include "Serialization.inl"
