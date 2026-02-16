#include <stdexcept>
#include <LittleNetwork/TCP/Sockets/ServerTCPSocket.hpp>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/TCP/Sockets/ClientTCPSocket.hpp>

namespace Ln
{
    ServerTCPSocket::ServerTCPSocket():TCPSocket()
    {
    }

    ServerTCPSocket::ServerTCPSocket(std::uint64_t sock):TCPSocket(sock)
    {
    
    }

    bool ServerTCPSocket::Listen(int backlog)
    {
        if (listen(m_sock, backlog) == SOCKET_ERROR)
        {
            fmt::print("WSA Error when Server TCP socket tried to listen: {}\n", WSAGetLastError());
            return false;
        }
    
        return true;
    }

    ClientTCPSocket ServerTCPSocket::Accept()
    {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSock = accept(m_sock, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSock == INVALID_SOCKET)
        {
            fmt::print("WSA Error when Server TCP socket tried to accept client: {}\n", WSAGetLastError());
        }

        ClientTCPSocket newClient(clientSock);
        newClient.SetOption(TCPSocketOption::NoDelay, true);
        return newClient;
    }
}
