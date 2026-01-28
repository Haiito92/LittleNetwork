#pragma once
#include <string>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    enum class AddressFamily
    {
        Inet,
        Inet6
    };
    
    struct LN_API IPAddress
    {
    public:
        AddressFamily family = AddressFamily::Inet;
        std::string address = "127.0.0.1";
        uint16_t port = 10001;
    };
}
