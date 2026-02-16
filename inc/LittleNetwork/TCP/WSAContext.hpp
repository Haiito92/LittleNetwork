#pragma once
#include <LittleNetwork/Export.hpp>

namespace LN
{
    class LN_API WSAContext
    {
    public:
        WSAContext();
        WSAContext(const WSAContext& other) = delete;
        WSAContext(WSAContext&& other) = delete;
        ~WSAContext();

        WSAContext& operator=(const WSAContext& other) = delete;
        WSAContext& operator=(WSAContext&& other) = delete;
    };
}
