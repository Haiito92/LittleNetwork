#pragma once
#include <WS2tcpip.h>
#include <LittleNetwork/Export.hpp>
#include <LittleNetwork/TCP/Sockets/TCPSocket.hpp>

namespace Ln
{
    class ClientTCPSocket;

    class LN_API ServerTCPSocket : public TCPSocket
    {
    public:
        ServerTCPSocket();
        ServerTCPSocket(std::uint64_t sock);
        ServerTCPSocket(const ServerTCPSocket& other) = delete;
        ServerTCPSocket(ServerTCPSocket&& other) noexcept = default;
        ~ServerTCPSocket() = default;
    
        ServerTCPSocket& operator=(const ServerTCPSocket& other) = delete;
        ServerTCPSocket& operator=(ServerTCPSocket&& other) noexcept = default;

        bool Listen(int backlog = 10);
        ClientTCPSocket Accept();
    };
}
