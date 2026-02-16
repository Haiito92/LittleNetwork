#pragma once
#include <map>
#include <type_traits>
#include <vector>
#include <string>
#include <LittleNetwork/Export.hpp>

namespace LN
{
    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value);

    template <typename T> requires std::is_arithmetic_v<T>
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset);

    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmeticVector(std::vector<std::uint8_t>& bytes, const std::vector<T>& vector);
    template <typename T> requires std::is_arithmetic_v<T>
    std::vector<T> DeserializeArithmeticVector(const std::vector<std::uint8_t>& bytes, size_t& offset);

    void SerializeString(std::vector<std::uint8_t>& bytes, const std::string& string);
    std::string DeserializeString(const std::vector<std::uint8_t>& bytes, size_t& offset);
}

#include "Serialization.inl"
