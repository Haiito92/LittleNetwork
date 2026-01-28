#include <stdexcept>
#include <LittleNetwork/ServerTCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/ClientTCPSocket.hpp>

namespace Ln
{
    ServerTCPSocket::ServerTCPSocket(): TCPSocket()
    {
        
    }

    ServerTCPSocket::~ServerTCPSocket() = default;

    void ServerTCPSocket::Listen(int backlog)
    {
        if (listen(m_sock, backlog) == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to put socket into listen mode ({})\n", WSAGetLastError()));
        }
    }

    ClientTCPSocket ServerTCPSocket::Accept()
    {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET client = accept(m_sock, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        if (client == INVALID_SOCKET)
        {
            throw std::runtime_error(fmt::format("Failed to accept new client ({})\n", WSAGetLastError()));
        }
        return ClientTCPSocket(client);
    }
}
