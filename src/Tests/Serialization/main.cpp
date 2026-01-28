#include <format>
#include <fmt/printf.h>
#include <LittleNetwork/Serialization.hpp>

int main(int argc, char** argv) {

    try
    {
        std::vector<uint8_t> bytes;

        bool fooBool = true;
        short fooShort = 4;
        uint16_t fooUint16 = 5;
        int fooInt = 51;
        uint32_t fooUint = 1024;
        uint64_t fooUint64 = 40000;
        float fooFloat = 7.5f;
        double fooDouble = 8.96;
        char fooChar = 'A';
        
        Ln::SerializeArithmetic(bytes, fooBool);
        Ln::SerializeArithmetic(bytes, fooShort);
        Ln::SerializeArithmetic(bytes, fooUint16);
        Ln::SerializeArithmetic(bytes, fooInt);
        Ln::SerializeArithmetic(bytes, fooUint);
        Ln::SerializeArithmetic(bytes, fooUint64);
        Ln::SerializeArithmetic(bytes, fooFloat);
        Ln::SerializeArithmetic(bytes, fooDouble);
        Ln::SerializeArithmetic(bytes, fooChar);

        fmt::print("Serialized Foo Bool: {} \n", fooBool);
        fmt::print("Serialized Foo Short: {} \n", fooShort);
        fmt::print("Serialized Foo UInt16: {} \n", fooUint16);
        fmt::print("Serialized Foo Int: {} \n", fooInt);
        fmt::print("Serialized Foo UInt32: {} \n", fooUint);
        fmt::print("Serialized Foo UInt64: {} \n", fooUint64);
        fmt::print("Serialized Foo Float: {} \n", fooFloat);
        fmt::print("Serialized Foo Double: {} \n", fooDouble);
        fmt::print("Serialized Foo Char: {} \n", fooChar);

        size_t offset = 0;
        bool deserializedFooBool = Ln::DeserializeArithmetic<bool>(bytes, offset);
        short deserializedFooShort = Ln::DeserializeArithmetic<short>(bytes, offset);
        uint16_t deserializedFooUint16 = Ln::DeserializeArithmetic<uint16_t>(bytes, offset);
        int deserializedFooInt = Ln::DeserializeArithmetic<int>(bytes, offset);
        uint32_t deserializedFooUint = Ln::DeserializeArithmetic<uint32_t>(bytes, offset);
        uint64_t deserializedFooUint64 = Ln::DeserializeArithmetic<uint64_t>(bytes, offset);
        float deserializedFooFloat = Ln::DeserializeArithmetic<float>(bytes, offset);
        double deserializedFooDouble = Ln::DeserializeArithmetic<double>(bytes, offset);
        char deserializedFooChar = Ln::DeserializeArithmetic<char>(bytes, offset);

        fmt::print("Deserialized Foo Bool: {} \n", deserializedFooBool);
        fmt::print("Deserialized Foo Short: {} \n", deserializedFooShort);
        fmt::print("Deserialized Foo UInt16: {} \n", deserializedFooUint16);
        fmt::print("Deserialized Foo Int: {} \n", deserializedFooInt);
        fmt::print("Deserialized Foo UInt32: {} \n", deserializedFooUint);
        fmt::print("Deserialized Foo UInt64: {} \n", deserializedFooUint64);
        fmt::print("Deserialized Foo Float: {} \n", deserializedFooFloat);
        fmt::print("Deserialized Foo Double: {} \n", deserializedFooDouble);
        fmt::print("Deserialized Foo Char: {} \n", deserializedFooChar);
        
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
