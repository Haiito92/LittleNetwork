#pragma once
#include <stdexcept>
#include <WinSock2.h>

namespace Ln
{
    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmetic(std::vector<std::uint8_t>& bytes, T value)
    {
        if constexpr (sizeof(T) > sizeof(std::uint64_t))
            throw std::runtime_error("Unsupported type size: type size is over 64 bites");

        size_t offset = bytes.size();

        if constexpr (sizeof(T) == sizeof(std::uint64_t))
        {
            uint64_t serializedValue = 0;
            if constexpr (std::is_same_v<T, double>)
            {
                serializedValue = htond(value);
            }
            else
            {
                serializedValue = htonll(value);
            }

            bytes.resize(offset + sizeof(uint64_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint64_t));
            return;
        }
        if constexpr (sizeof(T) == sizeof(std::uint32_t))
        {
            uint32_t serializedValue = 0;

            if constexpr (std::is_same_v<T, float>)
            {
                serializedValue = htonf(value);
            }
            else
            {
                serializedValue = htonl(value);
            }
            
            bytes.resize(offset + sizeof(uint32_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint32_t));
            return;
        }
        if constexpr (sizeof(T) == sizeof(std::uint16_t))
        {
            uint16_t serializedValue = htons(value);
            bytes.resize(offset + sizeof(uint16_t));
            std::memcpy(&bytes[offset], &serializedValue, sizeof(uint16_t));
            return;
        }
        if constexpr (sizeof(T) == sizeof(std::uint8_t))
        {
            bytes.resize(offset + sizeof(uint8_t));
            std::memcpy(&bytes[offset], &value, sizeof(uint8_t));
            return;
        }

        //throw std::runtime_error("Unsupported type size: value couldn't be serialized");
    }

    template <typename T> requires std::is_arithmetic_v<T>
    T DeserializeArithmetic(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        if constexpr (sizeof(T) > sizeof(std::uint64_t))
            throw std::runtime_error("Unsupported type size: type size is over 64 bites");
        
        if constexpr (sizeof(T) == sizeof(std::uint64_t))
        {
            uint64_t deserializedValue = 0;
            
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint64_t));
            offset += sizeof(uint64_t);

            if constexpr (std::is_same_v<T, double>)
            {
                return ntohd(deserializedValue);
            }
            else
            {
                return ntohll(deserializedValue);
            }
        }
        if constexpr (sizeof(T) == sizeof(std::uint32_t))
        {
            std::uint32_t deserializedValue = 0;
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint32_t));
            offset += sizeof(uint32_t);

            if constexpr (std::is_same_v<T, float>)
            {
                return ntohf(deserializedValue);
            }
            else
            {
                return ntohl(deserializedValue);
            }
        }
        if constexpr (sizeof(T) == sizeof(std::uint16_t))
        {
            std::uint16_t deserializedValue = 0;
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint16_t));
            offset += sizeof(uint16_t);

            return ntohs(deserializedValue);
        }
        if constexpr (sizeof(T) == sizeof(std::uint8_t))
        {
            std::uint8_t deserializedValue = 0;
            std::memcpy(&deserializedValue, &bytes[offset], sizeof(uint8_t));
            offset += sizeof(uint8_t);

            return deserializedValue;
        }

        //throw std::runtime_error("Unsupported type size: value couldn't be deserialized");
    }

    template <typename T> requires std::is_arithmetic_v<T>
    void SerializeArithmeticVector(std::vector<std::uint8_t>& bytes, const std::vector<T>& vector)
    {
        SerializeArithmetic(bytes, vector.size());

        for (const T& arithmetic : vector)
        {
            SerializeArithmetic(bytes, arithmetic);
        }
    }

    template <typename T> requires std::is_arithmetic_v<T>
    std::vector<T> DeserializeArithmeticVector(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        size_t size = DeserializeArithmetic<size_t>(bytes, offset);
        
        std::vector<T> vector(size);
        
        for (size_t i = 0; i < size; i++)
        {
            vector[i] = DeserializeArithmetic<T>(bytes, offset);
        }

        return vector;
    }
}
