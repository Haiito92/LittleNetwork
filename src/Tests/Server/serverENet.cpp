#include <format>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <vector>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/Sockets/ServerTCPSocket.hpp>
#include <LittleNetwork/Sockets/ClientTCPSocket.hpp>
#include <LittleNetwork/Sockets/IPAddress.hpp>
#include <LittleNetwork/Polling/Descriptor.hpp>
#include <LittleNetwork/Polling/Poller.hpp>
#include <LittleNetwork/Serialization/Serialization.hpp>


int main(int argc, char** argv) {

    try
    {
        while (true)
        {
            

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
}
