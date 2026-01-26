#include <format>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/TCPSocket.hpp>
#include <WS2tcpip.h>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;
        Ln::TCPSocket socket;

        sockaddr_in bindAddress;
        
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
