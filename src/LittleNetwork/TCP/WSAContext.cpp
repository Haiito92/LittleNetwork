#include <stdexcept>
#include <LittleNetwork/TCP/WSAContext.hpp>
#include <WinSock2.h>

namespace LN
{
    WSAContext::WSAContext()
    {
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (result != 0)
        {
            throw std::runtime_error("WSAStartup failed");
        }
    }

    WSAContext::~WSAContext()
    {
        WSACleanup();
    }
}
