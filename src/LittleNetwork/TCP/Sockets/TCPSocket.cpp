#include <stdexcept>
#include <LittleNetwork/TCP/Sockets/TCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/TCP/Sockets/IPAddress.hpp>

namespace Ln
{
    TCPSocket::TCPSocket():
    m_sock()
    {
        m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (m_sock == INVALID_SOCKET)
        {
            throw std::runtime_error(fmt::format("Failed to create TCP socket: {}\n", WSAGetLastError()));
        }

        SetOption(TCPSocketOption::NoDelay, true);
    }

    TCPSocket::TCPSocket(std::uint64_t sock)
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
        if (&other != this)
        {
            m_sock = other.m_sock;
            other.m_sock = INVALID_SOCKET;
        }

        return *this;
    }

    bool TCPSocket::Bind(const IPAddress& bindAddress)
    {
        sockaddr_in addr;
        
        switch (bindAddress.family)
        {
            case AddressFamily::Inet:
                {
                    addr.sin_family = AF_INET;
                    inet_pton(AF_INET, bindAddress.address.c_str(), &addr.sin_addr);
                    break;
                }
            case AddressFamily::Inet6:
                {
                    fmt::print("Failed to bind: address family not supported.\n");
                    return false;
                }
        }

        addr.sin_port = htons(bindAddress.port);
        
        if (bind(m_sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR)
        {
            fmt::print("WSA Error when binding TCP socket: {}\n", WSAGetLastError());
            return false;
        }

        return true;
    }

    std::uint64_t TCPSocket::GetHandle()
    {
        return m_sock;
    }

    std::uint64_t TCPSocket::GetHandle() const
    {
        return m_sock;
    }

    bool TCPSocket::SetOption(const TCPSocketOption& option, bool isOn)
    {
        std::uint16_t wsaOption;
        switch (option)
        {
            case TCPSocketOption::NoDelay: wsaOption = TCP_NODELAY; break;
            default:
                {
                    fmt::print("Failed to set TCP socket option: Unknown TCP Socket option\n");
                    return false;
                }
        }
        
        if (setsockopt(m_sock, IPPROTO_TCP, wsaOption, reinterpret_cast<const char*>(&isOn), sizeof(isOn)) == SOCKET_ERROR)
        {
            fmt::print("Failed to set TCP socket option ({})\n", WSAGetLastError());

            return false;
        }

        return true;
    }
}
