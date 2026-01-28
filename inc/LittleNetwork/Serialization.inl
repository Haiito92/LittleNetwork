#pragma once
#include <WinSock2.h>

namespace Ln
{
    template <typename T> requires std::is_arithmetic<T>::value
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value)
    {
        value = static_cast<T>(htond(static_cast<double>(value)));

        size_t offset = bytes.size();
        bytes.resize(offset + sizeof(T));
        std::memcpy(&bytes[offset], &value, sizeof(T));
    }

    template <typename T> requires std::is_arithmetic<T>::value
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        T value;
        
        std::memcpy(&value, &bytes[offset], sizeof(T));
        offset += sizeof(T);
        
        return static_cast<T>(ntohd(static_cast<unsigned long long>(value)));
    }
}
