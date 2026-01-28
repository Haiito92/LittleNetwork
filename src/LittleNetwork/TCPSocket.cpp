#include <stdexcept>
#include <LittleNetwork/TCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/IPAddress.hpp>

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

    TCPSocket::TCPSocket(TCPSocket&& other) noexcept:
    m_sock(other.m_sock)
    {
        other.m_sock = INVALID_SOCKET;
    }

    TCPSocket::~TCPSocket()
    {
        if (m_sock != INVALID_SOCKET)
        {
            closesocket(m_sock);
        }
    }

    TCPSocket& TCPSocket::operator=(TCPSocket&& other) noexcept
    {
        if (this != &other)
        {
            m_sock = other.m_sock;
            other.m_sock = INVALID_SOCKET;
        }

        return *this;
    }

    void TCPSocket::Bind(const IPAddress& bindAddr)
    {
        sockaddr_in sockAddr;
        
        switch (bindAddr.family)
        {
            case AddressFamily::Inet:
            {
                sockAddr.sin_family = AF_INET;
                inet_pton(AF_INET, bindAddr.address.c_str(), &sockAddr.sin_addr);
                break;
            }
            case AddressFamily::Inet6:
            {
                throw std::runtime_error(fmt::format("Address family not supported\n"));
            }
        }

        sockAddr.sin_port = htons(bindAddr.port);

        if (bind(m_sock, reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockAddr)) == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to bind socket ({})\n", WSAGetLastError()));
        }  
    }
    
    uint64_t TCPSocket::GetHandle() const
    {
        return m_sock;
    }
}
