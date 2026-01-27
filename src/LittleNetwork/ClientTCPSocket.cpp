#include <stdexcept>
#include <LittleNetwork/ClientTCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>

namespace Ln
{
    
    ClientTCPSocket::ClientTCPSocket(): TCPSocket()
    {
        
    }

    ClientTCPSocket::ClientTCPSocket(uint64_t sock): TCPSocket(sock)
    {
    }

    ClientTCPSocket::~ClientTCPSocket() = default;

    void ClientTCPSocket::Connect(const sockaddr_in& serverAddr)
    {
        if (connect(m_sock, reinterpret_cast<const sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to connect to server ({})\n", WSAGetLastError()));
        }
    }

    void ClientTCPSocket::Send(const std::string& message) const
    {
        if (send(m_sock, message.data(), message.size(), 0) == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to send answer to client ({})\n", WSAGetLastError()));
        }
    }

    int ClientTCPSocket::Receive(char* buffer) const
    {
        int byteRead = recv(m_sock, buffer, 1024*sizeof(char), 0);
        if (byteRead == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to read from client ({})\n", WSAGetLastError()));
        }

        return byteRead;
    }
}
