#include <stdexcept>
#include <LittleNetwork/TCP/Sockets/ClientTCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/TCP/Sockets/IPAddress.hpp>

namespace LN
{
    
    ClientTCPSocket::ClientTCPSocket():TCPSocket()
    {
    }

    ClientTCPSocket::ClientTCPSocket(std::uint64_t sock):TCPSocket(sock)
    {
        
    }

    bool ClientTCPSocket::Connect(const IPAddress& serverAddress)
    {
        sockaddr_in addr;
        
        switch (serverAddress.family)
        {
        case AddressFamily::Inet:
            {
                addr.sin_family = AF_INET;
                inet_pton(AF_INET, serverAddress.address.c_str(), &addr.sin_addr);
                break;
            }
        case AddressFamily::Inet6:
            {
                fmt::print("Failed to bind: address family not supported.\n");
                return false;
            }
        }

        addr.sin_port = htons(serverAddress.port);
        
        if (connect(m_sock, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            fmt::print("WSA Error when Client TCP socket tried to connect: {}\n", WSAGetLastError());
            return false;
        }

        return true;
    }

    bool ClientTCPSocket::Send(const std::vector<uint8_t>& bytes) const
    {
        if (send(m_sock, reinterpret_cast<const char*>(&bytes[0]), bytes.size(), 0) == SOCKET_ERROR)
        {
            fmt::print("WSA Error when Client TCP socket tried to send data: {}\n", WSAGetLastError());
            return false;
        }

        return true;
    }

    bool ClientTCPSocket::Receive(std::vector<uint8_t>& bytes, int& bytesRead) const
    {
        return Receive(m_sock, bytes, bytesRead);
    }

    bool ClientTCPSocket::Receive(std::uint64_t sock, std::vector<uint8_t>& bytes, int& bytesRead)
    {
        if (bytes.size() == 0)
        {
            fmt::print("Failed to Receive data: bytes size == 0\n");
            return false;
        }
        
        bytesRead = recv(sock, reinterpret_cast<char*>(&bytes[0]), bytes.size(), 0);

        if (bytesRead == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            
            if (error == WSAECONNRESET)
            {
                bytesRead = 0;
            }
            else
            {
                fmt::print("WSA Error when Client TCP socket tried to receive data: {}\n", error);
                return false;
            }
        }
        
        return true;
    }
}
