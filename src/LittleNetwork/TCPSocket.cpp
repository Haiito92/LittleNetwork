#include <stdexcept>
#include <LittleNetwork/TCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>

namespace Ln
{
    TCPSocket::TCPSocket()
    {
        m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_sock == INVALID_SOCKET)
        {
            throw std::runtime_error(fmt::format("Failed to create socket ({})\n", WSAGetLastError()));
        }
    }

    TCPSocket::TCPSocket(uint64_t sock)
    {
        m_sock = sock;
    }

    TCPSocket::~TCPSocket()
    {
        closesocket(m_sock);
    }

    void TCPSocket::Bind(const sockaddr_in& bindAddr)
    {
        if (bind(m_sock, reinterpret_cast<const sockaddr*>(&bindAddr), sizeof(bindAddr)) == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to bind socket ({})\n", WSAGetLastError()));
        }
    }
    
    uint64_t TCPSocket::GetHandle() const
    {
        return m_sock;
    }
}
