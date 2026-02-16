#include <stdexcept>
#include <LittleNetwork/ENet/ENetContext.hpp>
#include <enet6/enet.h>

namespace LN
{
    ENetContext::ENetContext()
    {
        if (enet_initialize() < 0)
            throw std::runtime_error("enet_initialize() failed: {}");
    }

    ENetContext::~ENetContext()
    {
        enet_deinitialize();
    }
}
