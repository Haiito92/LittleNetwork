#pragma once
#include <memory>
#include <WS2tcpip.h>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    class LN_API TCPSocket
    {
    public:
        TCPSocket();
        TCPSocket(uint64_t sock);
        TCPSocket(const TCPSocket& other) = delete;
        TCPSocket(TCPSocket&& other) noexcept = default;
        ~TCPSocket();

        TCPSocket& operator=(const TCPSocket& other) = delete;
        TCPSocket& operator=(TCPSocket&& other) noexcept = default;

        void Bind(const sockaddr_in& bindAddr);
        
        uint64_t GetHandle() const;
        
    protected:
        uint64_t m_sock;
    };
}
