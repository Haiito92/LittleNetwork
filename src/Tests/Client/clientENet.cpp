#include <chrono>
#include <format>
#include <thread>
#include <fmt/printf.h>
#include <conio.h>
#include <iostream>
#include <LittleNetwork/Serialization/Serialization.hpp>
#include <LittleNetwork/ENet/ENetContext.hpp>


int main(int argc, char** argv) {

    try
    {
        LN::ENetContext enetContext;

        
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
                    fmt::print("Try send float.\n");
                    
                    std::vector<std::uint8_t> bytes;

                    float myFloat = 32.32f;
                    LN::SerializeArithmetic(bytes, myFloat);

                    // if (!clientSock.Send(bytes))
                    // {
                    //     fmt::print("Failed to send data to server.\n");
                    // }
                }
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
}
