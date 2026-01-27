#include <chrono>
#include <format>
#include <thread>
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

        while (true)
        {
            // std::string response = "Hello world!";
            // clientSocket.Send(response);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
