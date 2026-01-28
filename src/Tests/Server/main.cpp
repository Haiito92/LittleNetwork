#include <format>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/ServerTCPSocket.hpp>
#include <LittleNetwork/ClientTCPSocket.hpp>
#include <LittleNetwork/IPAddress.hpp>
#include <vector>


int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ServerTCPSocket sockServer;

        Ln::IPAddress bindAddr;
        bindAddr.family = Ln::AddressFamily::Inet;
        bindAddr.address = "0.0.0.0";
        bindAddr.port = 10001;
        
        sockServer.Bind(bindAddr);
        sockServer.Listen();

        std::vector<Ln::ClientTCPSocket> clientSockets;

        while (true)
        {
            std::vector<WSAPOLLFD> descriptors;
            {
                WSAPOLLFD descriptor;
                descriptor.fd = sockServer.GetHandle();
                descriptor.events = POLLIN;
                descriptor.revents = 0;
                descriptors.push_back(descriptor);
            }

            for (const Ln::ClientTCPSocket& socket : clientSockets)
            {
                WSAPOLLFD descriptor;
                descriptor.fd = socket.GetHandle();
                descriptor.events = POLLIN;
                descriptor.revents = 0;

                descriptors.push_back(descriptor);
            }

            // Ask why timeout == -1
            int activeSocketCount = WSAPoll(descriptors.data(), descriptors.size(), -1);

            if (activeSocketCount == 0)
            {
                throw std::runtime_error(fmt::format("Error when polling: {}\n", WSAGetLastError()));
            }

            for (WSAPOLLFD& descriptor : descriptors)
            {
                if (descriptor.revents == 0)
                    continue;

                if (descriptor.fd == sockServer.GetHandle())
                {
                    clientSockets.emplace_back(sockServer.Accept());
                }
                else
                {
                    char buffer[1024];
                    int byteRead = Ln::ClientTCPSocket::Receive(descriptor.fd, buffer);
                    if (byteRead == 0 || byteRead == SOCKET_ERROR)
                    {
                        if (byteRead == SOCKET_ERROR)
                            fmt::print("Failed to read from client ({})\n", WSAGetLastError());
					
                        //fmt::print("Client disconnected\n");

                        auto it = std::find_if(clientSockets.begin(), clientSockets.end(), [&](const Ln::ClientTCPSocket& socket)
                        {
                            return socket.GetHandle() == descriptor.fd;
                        });
                        
                        clientSockets.erase(it);
                        continue;
                    }

                    std::string clientMessage = fmt::format("{}: {}", descriptor.fd, std::string_view(buffer, byteRead));
                    fmt::print("{}\n", clientMessage);
                    
                    for (const Ln::ClientTCPSocket& socket : clientSockets)
                    {
                        if (socket.GetHandle() == descriptor.fd) continue;
                        socket.Send(clientMessage);
                    }
                }
            }

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
