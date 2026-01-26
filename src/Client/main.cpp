#include <format>
#include <WinSock2.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        
        sockaddr_in clientIp;
        clientIp.sin_family = AF_INET;
        clientIp.sin_port = htons(1337);
        clientIp.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if (connect(sock, reinterpret_cast<sockaddr*>(&clientIp), sizeof(clientIp)) == SOCKET_ERROR)
        {
            fmt::print("Failed to connect to server ({})\n", WSAGetLastError());
            return EXIT_FAILURE;
        }

        std::string response = "Hello world!";
        if (send(sock, response.data(), response.size(), 0) == SOCKET_ERROR)
        {
            fmt::print("Failed to send answer to client ({})\n", WSAGetLastError());
            return EXIT_FAILURE;
        }
        
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
