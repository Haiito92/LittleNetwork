#include <format>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in bindAddr;
        bindAddr.sin_addr.s_addr = INADDR_ANY;
        bindAddr.sin_port = htons(1337);
        bindAddr.sin_family = AF_INET;

        if (bind(sock, reinterpret_cast<sockaddr*>(&bindAddr), sizeof(bindAddr)) == SOCKET_ERROR)
        {
            fmt::print("Failed to bind socket ({})\n", WSAGetLastError());
            return EXIT_FAILURE;
        }
        if (listen(sock, 10) == SOCKET_ERROR)
        {
            fmt::print("Failed to put socket into listen mode ({})\n", WSAGetLastError());
            return EXIT_FAILURE;
        }

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET client = accept(sock, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        if (client == INVALID_SOCKET)
        {
            fmt::print("Failed to accept new client ({})\n", WSAGetLastError());
            return EXIT_FAILURE;
        }

        char buffer[1024];
        int byteRead = recv(client, buffer, 1024*sizeof(char), 0);
        if (byteRead == SOCKET_ERROR)
        {
            fmt::print("Failed to read from client ({})\n", WSAGetLastError());
            
            return EXIT_FAILURE;
        }

        fmt::print("Received {} bytes from client: ({})\n",byteRead, std::string_view(buffer, byteRead));

        closesocket(client);
        closesocket(sock);
    }
    catch (std::exception& e)
    {
        fmt::print("Catched standard exception: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("Catched unknown exception\n");
    }

    return 0;
}
