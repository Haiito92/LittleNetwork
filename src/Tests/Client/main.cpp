#include <format>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/ClientTCPSocket.hpp>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ClientTCPSocket clientSocket;
        
        sockaddr_in serverIp;
        serverIp.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &serverIp.sin_addr);
        serverIp.sin_port = htons(10001);
        
        clientSocket.Connect(serverIp);
        
        std::string response = "Hello world!";
        clientSocket.Send(response);

        char buffer[1024];
        int byteRead = clientSocket.Receive(buffer);
        
        fmt::print("Received {} bytes from client: ({})\n",byteRead, std::string_view(buffer, byteRead));
    
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
