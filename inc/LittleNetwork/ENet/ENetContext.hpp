#pragma once
#include <LittleNetwork/Export.hpp>

namespace LN
{
    class LN_API ENetContext
    {
    public:
        ENetContext();
        ENetContext(const ENetContext& other) = delete;
        ENetContext(ENetContext&& other) = delete;
        ~ENetContext();

        ENetContext& operator=(const ENetContext& other) = delete;
        ENetContext& operator=(ENetContext&& other) = delete;
    };
}
