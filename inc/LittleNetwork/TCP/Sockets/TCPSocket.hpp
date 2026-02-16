#pragma once
#include <memory>
#include <WS2tcpip.h>
#include <LittleNetwork/Export.hpp>

namespace LN
{
    struct IPAddress;
    enum class TCPSocketOption: std::uint8_t;

    class LN_API TCPSocket
    {
    public:
        TCPSocket();
        TCPSocket(std::uint64_t sock);
        TCPSocket(const TCPSocket& other) = delete;
        TCPSocket(TCPSocket&& other) noexcept;
        ~TCPSocket();
    
        TCPSocket& operator=(const TCPSocket& other) = delete;
        TCPSocket& operator=(TCPSocket&& other) noexcept;

        bool Bind(const IPAddress& bindAddress);

        std::uint64_t GetHandle();
        std::uint64_t GetHandle() const;

        bool SetOption(const TCPSocketOption& option, bool isOn);

        static constexpr std::uint64_t InvalidSocket = INVALID_SOCKET;
    
    protected:
        std::uint64_t m_sock;
    };

    enum class LN_API TCPSocketOption: std::uint8_t
    {
        NoDelay
    };
}
