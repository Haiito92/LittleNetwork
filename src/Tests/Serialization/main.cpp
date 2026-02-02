#include <format>
#include <fmt/printf.h>
#include <LittleNetwork/Serialization.hpp>

int main(int argc, char** argv) {

    try
    {
        std::vector<uint8_t> bytes;
        size_t offset = 0;

        // bool fooBool = true;
        // short fooShort = 4;
        // uint16_t fooUint16 = 5;
        // int fooInt = 51;
        // uint32_t fooUint = 1024;
        // uint64_t fooUint64 = 40000;
        // float fooFloat = 7.5f;
        // double fooDouble = 8.96;
        // char fooChar = 'A';
        //
        // Ln::SerializeArithmetic(bytes, fooBool);
        // Ln::SerializeArithmetic(bytes, fooShort);
        // Ln::SerializeArithmetic(bytes, fooUint16);
        // Ln::SerializeArithmetic(bytes, fooInt);
        // Ln::SerializeArithmetic(bytes, fooUint);
        // Ln::SerializeArithmetic(bytes, fooUint64);
        // Ln::SerializeArithmetic(bytes, fooFloat);
        // Ln::SerializeArithmetic(bytes, fooDouble);
        // Ln::SerializeArithmetic(bytes, fooChar);
        //
        // fmt::print("Serialized Foo Bool: {} \n", fooBool);
        // fmt::print("Serialized Foo Short: {} \n", fooShort);
        // fmt::print("Serialized Foo UInt16: {} \n", fooUint16);
        // fmt::print("Serialized Foo Int: {} \n", fooInt);
        // fmt::print("Serialized Foo UInt32: {} \n", fooUint);
        // fmt::print("Serialized Foo UInt64: {} \n", fooUint64);
        // fmt::print("Serialized Foo Float: {} \n", fooFloat);
        // fmt::print("Serialized Foo Double: {} \n", fooDouble);
        // fmt::print("Serialized Foo Char: {} \n", fooChar);
        //
        
        // bool deserializedFooBool = Ln::DeserializeArithmetic<bool>(bytes, offset);
        // short deserializedFooShort = Ln::DeserializeArithmetic<short>(bytes, offset);
        // uint16_t deserializedFooUint16 = Ln::DeserializeArithmetic<uint16_t>(bytes, offset);
        // int deserializedFooInt = Ln::DeserializeArithmetic<int>(bytes, offset);
        // uint32_t deserializedFooUint = Ln::DeserializeArithmetic<uint32_t>(bytes, offset);
        // uint64_t deserializedFooUint64 = Ln::DeserializeArithmetic<uint64_t>(bytes, offset);
        // float deserializedFooFloat = Ln::DeserializeArithmetic<float>(bytes, offset);
        // double deserializedFooDouble = Ln::DeserializeArithmetic<double>(bytes, offset);
        // char deserializedFooChar = Ln::DeserializeArithmetic<char>(bytes, offset);
        //
        // fmt::print("Deserialized Foo Bool: {} \n", deserializedFooBool);
        // fmt::print("Deserialized Foo Short: {} \n", deserializedFooShort);
        // fmt::print("Deserialized Foo UInt16: {} \n", deserializedFooUint16);
        // fmt::print("Deserialized Foo Int: {} \n", deserializedFooInt);
        // fmt::print("Deserialized Foo UInt32: {} \n", deserializedFooUint);
        // fmt::print("Deserialized Foo UInt64: {} \n", deserializedFooUint64);
        // fmt::print("Deserialized Foo Float: {} \n", deserializedFooFloat);
        // fmt::print("Deserialized Foo Double: {} \n", deserializedFooDouble);
        // fmt::print("Deserialized Foo Char: {} \n", deserializedFooChar);

        // std::vector<std::uint8_t> values = {12, 54, 254, 127, 3};
        // Ln::SerializeArithmeticVector(bytes, values);
        //
        // std::vector<std::uint8_t> deserializedValues = Ln::DeserializeArithmeticVector(bytes, offset);
        // for (const std::uint8_t& deserializedValue : deserializedValues)
        // {
        //     fmt::print("Deserialized value: {} \n", deserializedValue);
        // }

        // std::string string = "Je suis malade!";
        // fmt::print("Serialized String: {} \n", string);
        // Ln::SerializeString(bytes, string);
        //
        // std::string deserializedString = Ln::DeserializeString(bytes, offset);
        // fmt::print("Deserialized String: {} \n", string);

        // std::map<std::uint8_t, std::uint8_t> values;
        // values[5] = 6;
        // values[42] = 57;
        // values[245] = 132;
        // Ln::SerializeArithmeticMap(bytes, values);
        //
        // std::map<std::uint8_t, std::uint8_t> deserializedValues = Ln::DeserializeArithmeticMap(bytes, offset);
        // for (const auto& deserializedPair : deserializedValues)
        // {
        //     fmt::print("Deserialized key: {} \n", deserializedPair.first);
        //     fmt::print("Deserialized value: {} \n", deserializedPair.second);
        // }

        // int a = 2;
        // int b = 8;
        //
        // uint8_t byte = 0;
        // byte |= a;
        // byte |= (b<<4);
        //
        // // 1000 0010
        // Ln::SerializeArithmetic(bytes, byte);
        //
        // uint8_t deserializeByte = Ln::DeserializeArithmetic<uint8_t>(bytes, offset);
        //
        // int dA = byte & 15;
        // byte >>= 4;
        // int dB = byte & 15;
        // fmt::print("Deserialized a: {} \n", dA);
        // fmt::print("Deserialized b: {} \n", dB);
    }
    catch (std::exception& e)
    {
        fmt::print("Catched standard exception: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("Catched unknown exception\n");
    }

    return 0;
}
