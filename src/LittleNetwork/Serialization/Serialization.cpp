#include <LittleNetwork/Serialization/Serialization.hpp>

namespace Ln
{
    void SerializeString(std::vector<std::uint8_t>& bytes, const std::string& string)
    {
        SerializeArithmetic(bytes, string.size());

        for (const char& c : string)
        {
            SerializeArithmetic(bytes, c); 
        }
    }

    std::string DeserializeString(const std::vector<std::uint8_t>& bytes, size_t& offset)
    {
        size_t size = DeserializeArithmetic<size_t>(bytes, offset);

        std::string string;
        string.resize(size);
    
        for (size_t i = 0; i < size; i++)
        {
            string[i] = DeserializeArithmetic<char>(bytes, offset);
        }

        return string;
    }
}
