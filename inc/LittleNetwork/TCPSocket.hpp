#pragma once
#include <memory>
#include <LittleNetwork/Export.hpp>
#include <LittleNetwork/Forward.hpp>

namespace Ln
{
    class LN_API TCPSocket
    {
    public:
        TCPSocket();
        TCPSocket(const TCPSocket& other) = delete;
        TCPSocket(TCPSocket&& other) = delete;
        ~TCPSocket();

        TCPSocket& operator=(const TCPSocket& other) = delete;
        TCPSocket& operator=(TCPSocket&& other) = delete;

        SocketID GetHandle() const;
    private:
        struct Impl;

        std::unique_ptr<Impl> m_impl;
    };
}
