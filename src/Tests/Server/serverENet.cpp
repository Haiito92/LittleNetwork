#include <format>
#include <thread>
#include <fmt/printf.h>
#include <vector>
#include <LittleNetwork/Serialization/Serialization.hpp>
#include <LittleNetwork/ENet/ENetContext.hpp>

#include "LittleNetwork/ENet/ENetHostEx.hpp"


int main(int argc, char** argv) {

    try
    {
        LN::ENetContext enetContext;

        
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
