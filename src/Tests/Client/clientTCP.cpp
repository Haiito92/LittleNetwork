#include <chrono>
#include <format>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <conio.h>
#include <iostream>
#include <LittleNetwork/TCP/WSAContext.hpp>
#include <LittleNetwork/TCP/Sockets/ClientTCPSocket.hpp>
#include <LittleNetwork/TCP/Sockets/IPAddress.hpp>
#include <LittleNetwork/TCP/Polling/Descriptor.hpp>
#include <LittleNetwork/TCP/Polling/Poller.hpp>
#include <LittleNetwork/Serialization/Serialization.hpp>


int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ClientTCPSocket clientSock;

        Ln::IPAddress address;
        address.family = Ln::AddressFamily::Inet;
        address.address = "127.0.0.1";
        address.port = 10001;

        if (!clientSock.Connect(address))
            return EXIT_FAILURE;

        Ln::Poller clientPoller;

        Ln::Descriptor clientDescriptor;
        clientDescriptor.sock = clientSock.GetHandle();
        clientPoller.AddDescriptor(clientDescriptor);
        
        bool isRunning = true;
        while (isRunning)
        {
            if (_kbhit())
            {
                char c = _getch(); 
                if (c == '\b')
                {
                    isRunning = false;
                    continue;
                }
                else if (c == '\r')
                {
                    std::vector<std::uint8_t> bytes;

                    fmt::print("\n## Test with strings ##\n\n");
                    
                    std::string message = "Jérémy je t'aime si tu vois ce message !";
                    Ln::SerializeString(bytes, message);

                    if (!clientSock.Send(bytes))
                    {
                        fmt::print("Failed to send data to server.\n");
                    }
                }
            }

            if (!clientPoller.Poll(0))
            {
                continue;
            }

            const Ln::Descriptor& descriptor = clientPoller.GetDescriptorAtIndex(0);

            if (descriptor.revents == 0)
                continue;
        
            if (descriptor.sock == clientSock.GetHandle())
            {
                // we do nothing on receive in this test
            }
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
