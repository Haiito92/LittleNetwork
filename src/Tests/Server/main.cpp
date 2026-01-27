#include <format>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/ServerTCPSocket.hpp>
#include <LittleNetwork/ClientTCPSocket.hpp>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ServerTCPSocket sockServer;
        sockaddr_in bindAddr;
        inet_pton(AF_INET, "0.0.0.0", &bindAddr.sin_addr);
        bindAddr.sin_port = htons(10001);
        bindAddr.sin_family = AF_INET;

        sockServer.Bind(bindAddr);
        sockServer.Listen();

        sockaddr_in clientAddr;
        Ln::ClientTCPSocket sockClient = sockServer.Accept(clientAddr);

        char buffer[1024];
        int byteRead = sockClient.Receive(buffer);
        
        fmt::print("Received {} bytes from client: ({})\n",byteRead, std::string_view(buffer, byteRead));
    
        std::string body = "<html><body><center><h1>Hello World!</h1></center></body></html>";
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Connection: Closed\r\n";
        response += "\r\n";
        response += body;
        
        sockClient.Send(response);

        
        byteRead = sockClient.Receive(buffer);
        if (byteRead == 0)
        {
            fmt::print("Client Disconnected gracefully!\n");
        }
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
