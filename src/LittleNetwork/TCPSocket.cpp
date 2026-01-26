#include <stdexcept>
#include <WinSock2.h>
#include <fmt/format.h>
#include <LittleNetwork/TCPSocket.hpp>

namespace Ln
{
    struct TCPSocket::Impl
    {
    public:
        SocketID socket;
    };
    
    TCPSocket::TCPSocket():
    m_impl(std::make_unique<Impl>())
    {
        m_impl->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (m_impl->socket == INVALID_SOCKET)
        {
            throw std::runtime_error(fmt::format("Failed to create socket: {}", WSAGetLastError()));
        }
    }

    TCPSocket::~TCPSocket()
    {
        closesocket(m_impl->socket);
    }

    SocketID TCPSocket::GetHandle() const
    {
        return m_impl->socket;
    }
}
