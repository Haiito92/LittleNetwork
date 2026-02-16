#pragma once
#include <string>
#include <LittleNetwork/Export.hpp>

namespace LN
{
    enum class AddressFamily : std::uint8_t
    {
        Inet,
        Inet6
    };
    
    struct LN_API IPAddress
    {
    public:
        AddressFamily family = AddressFamily::Inet;
        std::string address = "127.0.0.1";
        std::uint16_t port = 10001;
    };
}
