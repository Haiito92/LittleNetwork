#pragma once
#include <WS2tcpip.h>
#include <LittleNetwork/Export.hpp>
#include <LittleNetwork/TCPSocket.hpp>

namespace Ln
{
    class ClientTCPSocket;
    
    class LN_API ServerTCPSocket : public TCPSocket
    {
    public:
        ServerTCPSocket();
        ServerTCPSocket(const ServerTCPSocket& other) = delete;
        ServerTCPSocket(ServerTCPSocket&& other) noexcept = default;
        ~ServerTCPSocket();

        ServerTCPSocket& operator=(const ServerTCPSocket& other) = delete;
        ServerTCPSocket& operator=(ServerTCPSocket&& other) noexcept = default;

        void Listen(int backlog = 10);
        ClientTCPSocket Accept();
    };
}
