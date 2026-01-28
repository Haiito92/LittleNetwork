#pragma once
#include <string>
#include <WS2tcpip.h>
#include <LittleNetwork/Export.hpp>
#include <LittleNetwork/TCPSocket.hpp>

namespace Ln
{
    class LN_API ClientTCPSocket : public TCPSocket
    {
    public:
        ClientTCPSocket();
        ClientTCPSocket(uint64_t sock);
        ClientTCPSocket(const ClientTCPSocket& other) = delete;
        ClientTCPSocket(ClientTCPSocket&& other) noexcept = default;
        ~ClientTCPSocket();

        ClientTCPSocket& operator=(const ClientTCPSocket& other) = delete;
        ClientTCPSocket& operator=(ClientTCPSocket&& other) noexcept = default;

        void Connect(const IPAddress& serverAddr);

        void Send(const std::string& message) const;
        int Receive(char* buffer) const;

        static int Receive(uint64_t socket, char* buffer);
    };
}
