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
#include <LittleNetwork/Descriptor.hpp>
#include <LittleNetwork/Poller.hpp>

#include "LittleNetwork/Serialization.hpp"


int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ServerTCPSocket serverSock;

        Ln::IPAddress address;
        address.family = Ln::AddressFamily::Inet;
        address.address = "0.0.0.0";
        address.port = 10001;
    
        if (!serverSock.Bind(address))
            return EXIT_FAILURE;
        if (!serverSock.Listen())
            return EXIT_FAILURE;

        std::vector<Ln::ClientTCPSocket> clientSockets;

        Ln::Poller serverPoller;
        
        {
            Ln::Descriptor serverDescriptor;
            serverDescriptor.sock = serverSock.GetHandle();
            serverPoller.AddDescriptor(serverDescriptor);
        }
        
        while (true)
        {
            if (!serverPoller.Poll(1))
            {
                continue;
            }

            serverPoller.ForEachDescriptor([&](const Ln::Descriptor& descriptor)
            {
                 if (descriptor.revents == 0)
                    return;

                if (descriptor.sock == serverSock.GetHandle())
                {
                    Ln::ClientTCPSocket newClient = serverSock.Accept();
                    if (newClient.GetHandle() == Ln::TCPSocket::InvalidSocket)
                    {
                        fmt::print("Failed to accept client\n");
                        return;
                    }

                    Ln::Descriptor clientDescriptor;
                    clientDescriptor.sock = newClient.GetHandle();
                    serverPoller.AddDescriptor(clientDescriptor);
                    
                    clientSockets.push_back(std::move(newClient));
                    
                    fmt::print("Client accepted\n");
                }
                else
                {
                    std::vector<uint8_t> bytes(1024); // << On créé un byte vector de taille 1024 (on va recevoir au maximum 1024 bytes)
                    int bytesRead = 0; // << ce int sert à connaître le nombre de bytes réellement lu.
                    
                    if (!Ln::ClientTCPSocket::Receive(descriptor.sock, bytes, bytesRead))
                    {
                        fmt::print("Client received failed\n");
                        return;
                    }
                    
                    if (bytesRead == 0)
                    {
                        fmt::print("Client disconnected\n");

                        auto it = std::find_if(clientSockets.begin(), clientSockets.end(), [&](const Ln::ClientTCPSocket& socket)
                        {
                            return socket.GetHandle() == descriptor.sock;
                        });

                        if (it != clientSockets.end())
                        {
                            serverPoller.RemoveDescriptor(it->GetHandle());
                        
                            clientSockets.erase(it);
                        }
                        return;
                    }

                    size_t offset = 0;

                    // TEST WITH STRINGS //
                    
                    fmt::print("\n## Test with strings ##\n\n");
                    
                    std::string message = Ln::DeserializeString(bytes, offset);
                    
                    fmt::print("Received string: {}\n", message);
                }
            });
        }
        
        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        throw std::runtime_error(fmt::format("Exception occured: {}\n", e.what()));
    }
    catch (...)
    {
        throw std::runtime_error(fmt::format("Unknown exception occured\n"));
    }

    return 0;
}
