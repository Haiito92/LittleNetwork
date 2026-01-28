#include <stdexcept>
#include <LittleNetwork/ClientTCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/IPAddress.hpp>

namespace Ln
{
    
    ClientTCPSocket::ClientTCPSocket(): TCPSocket()
    {
        
    }

    ClientTCPSocket::ClientTCPSocket(uint64_t sock): TCPSocket(sock)
    {
    }

    ClientTCPSocket::~ClientTCPSocket() = default;

    void ClientTCPSocket::Connect(const IPAddress& serverAddr)
    {
        sockaddr_in sockAddr;
        
        switch (serverAddr.family)
        {
            case AddressFamily::Inet:
            {
                sockAddr.sin_family = AF_INET;
                inet_pton(AF_INET, serverAddr.address.c_str(), &sockAddr.sin_addr);
                break;
            }
            case AddressFamily::Inet6:
            {
                throw std::runtime_error(fmt::format("Address family not supported\n"));
            }
        }

        sockAddr.sin_port = htons(serverAddr.port);

        if (connect(m_sock, reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockAddr)) == SOCKET_ERROR)
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
        return Receive(m_sock, buffer);
    }

    int ClientTCPSocket::Receive(uint64_t socket, char* buffer)
    {
        int byteRead = recv(socket, buffer, sizeof(buffer), 0);
        if (byteRead == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Failed to read from client ({})\n", WSAGetLastError()));
        }

        return byteRead;
    }
}
