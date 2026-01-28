#pragma once
#include <WinSock2.h>

namespace Ln
{
    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value)
    {
        if constexpr (sizeof(T) > sizeof(uint64_t))
            throw std::runtime_error("Type Size not supported for serialization");
            
        size_t offset = bytes.size();
        
        if constexpr (std::is_same_v<T, double>)
        {
            uint64_t serializedValue = htond(value);
            bytes.resize(offset + sizeof(uint64_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint64_t));
            return;
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            uint32_t serializedValue = htonf(value);
            bytes.resize(offset + sizeof(uint32_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint32_t));
            return;
        }
        else if constexpr (sizeof(T) == sizeof(uint64_t))
        {
            uint64_t serializedValue = htonll(value);
            bytes.resize(offset + sizeof(uint64_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint64_t));
            return;
        }
        else if constexpr (sizeof(T) == sizeof(uint32_t))
        {
            uint32_t serializedValue = htonl(value);
            bytes.resize(offset + sizeof(uint32_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint32_t));
            return;
        }
        else if constexpr (sizeof(T) == sizeof(uint16_t))
        {
            uint16_t serializedValue = htons(value);
            bytes.resize(offset + sizeof(uint16_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint16_t));
            return;
        }
        else if constexpr (sizeof(T) == sizeof(uint8_t))
        {
            bytes.resize(offset + sizeof(uint8_t));
            std::memcpy(&bytes[offset], &value, sizeof(uint8_t));
            return;
        }
        
        throw std::runtime_error("Unsupported Type Size for serialization");
    }

    template <typename T> requires std::is_arithmetic_v<T>
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        if constexpr (sizeof(T) > sizeof(uint64_t))
            throw std::runtime_error("Type Size not supported for deserialization");
        
        if constexpr (std::is_same_v<T, double>)
        {
            uint64_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint64_t));
            offset += sizeof(uint64_t);

            return ntohd(deserializedValue);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            uint32_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint32_t));
            offset += sizeof(uint32_t);

            return ntohf(deserializedValue);
        }
        else if constexpr (sizeof(T) == sizeof(uint64_t))
        {
            uint64_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint64_t));
            offset += sizeof(uint64_t);

            return ntohll(deserializedValue);
        }
        else if constexpr (sizeof(T) == sizeof(uint32_t))
        {
            uint32_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint32_t));
            offset += sizeof(uint32_t);

            return ntohl(deserializedValue);
        }
        else if constexpr (sizeof(T) == sizeof(uint16_t))
        {
            uint16_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint16_t));
            offset += sizeof(uint16_t);

            return ntohs(deserializedValue);
        }
        else if constexpr (sizeof(T) == sizeof(uint8_t))
        {
            uint8_t deserializedValue;
        
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint8_t));
            offset += sizeof(uint8_t);

            return deserializedValue;
        }
        
        throw std::runtime_error("Unsupported Type Size for deserialization");
    }
}
