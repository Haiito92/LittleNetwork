#include <LittleNetwork/Serialization.hpp>

namespace Ln
{
    void SerializeArithmeticVector(std::vector<std::uint8_t>& bytes, const std::vector<std::uint8_t>& values)
    {
        SerializeArithmetic(bytes, values.size());
        for (const uint8_t& value : values)
        {
            SerializeArithmetic(bytes, value);
        }
    }

    std::vector<std::uint8_t> DeserializeArithmeticVector(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        size_t vectorSize = DeserializeArithmetic<size_t>(bytes, offset);
        std::vector<std::uint8_t> values(vectorSize);

        for (size_t i = 0; i < vectorSize; ++i)
        {
            values[i] = DeserializeArithmetic<uint8_t>(bytes, offset);
        }

        return values;
    }

    void SerializeArithmeticMap(std::vector<std::uint8_t>& bytes, const std::map<std::uint8_t, std::uint8_t>& values)
    {
        SerializeArithmetic(bytes, values.size());

        for (const auto& pair : values)
        {
            SerializeArithmetic(bytes, pair.first);
            SerializeArithmetic(bytes, pair.second);
        }
    }

    std::map<std::uint8_t, std::uint8_t> DeserializeArithmeticMap(const std::vector<std::uint8_t>& bytes,
        size_t& offset)
    {
        size_t mapSize = DeserializeArithmetic<size_t>(bytes, offset);
        
        std::map<std::uint8_t, std::uint8_t> values;
        
        for (size_t i = 0; i < mapSize; ++i)
        {
            std::uint8_t key = DeserializeArithmetic<uint8_t>(bytes, offset);
            std::uint8_t value = DeserializeArithmetic<uint8_t>(bytes, offset);
            values[key] = value;
        }

        return values;
    }

    void SerializeString(std::vector<std::uint8_t>& bytes, const std::string& string)
    {
        SerializeArithmetic(bytes, string.size());
        for (const char& value : string)
        {
            SerializeArithmetic(bytes, value);
        }
    }

    std::string DeserializeString(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        size_t stringSize = DeserializeArithmetic<size_t>(bytes, offset);
        std::string string;
        string.resize(stringSize);

        for (size_t i = 0; i < stringSize; ++i)
        {
            string[i] = DeserializeArithmetic<char>(bytes, offset);
        }

        return string;
    }
}
