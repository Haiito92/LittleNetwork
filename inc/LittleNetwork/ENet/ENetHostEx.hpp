#pragma once
#include <memory>
#include <LittleNetwork/Export.hpp>

namespace LN
{
    
    class LN_API ENetHostEx
    {
    public:
        ENetHostEx() = delete;
        ENetHostEx(size_t amountOfPeer);
        ENetHostEx(const ENetHostEx& other) = delete;
        ENetHostEx(ENetHostEx&& other) = delete;
        ~ENetHostEx();

        ENetHostEx& operator=(const ENetHostEx& other) = delete;
        ENetHostEx& operator=(ENetHostEx&& other) = delete;

    private:
        struct Impl;

        std::unique_ptr<Impl> m_impl;
    };
}
