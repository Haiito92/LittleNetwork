#pragma once
#include <vector>
#include <LittleNetwork/Export.hpp>
#include <LittleNetwork/TCPSocket.hpp>

namespace Ln
{
    class LN_API ClientTCPSocket : public TCPSocket
    {
    public:
        ClientTCPSocket();
        ClientTCPSocket(std::uint64_t sock);
        ClientTCPSocket(const ClientTCPSocket& other) = delete;
        ClientTCPSocket(ClientTCPSocket&& other) noexcept = default;
        ~ClientTCPSocket() = default;
    
        ClientTCPSocket& operator=(const ClientTCPSocket& other) = delete;
        ClientTCPSocket& operator=(ClientTCPSocket&& other) noexcept = default;

        bool Connect(const IPAddress& serverAddress);

        bool Send(const std::vector<uint8_t>& bytes) const;
        bool Receive(std::vector<uint8_t>& bytes, int& bytesRead) const;
        static bool Receive(std::uint64_t sock, std::vector<uint8_t>& bytes, int& bytesRead);
    };
}
