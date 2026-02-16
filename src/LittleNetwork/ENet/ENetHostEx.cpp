#include <stdexcept>
#include <LittleNetwork/ENet/ENetHostEx.hpp>
#include <enet6/enet.h>

namespace LN
{
    struct ENetHostEx::Impl
    {
        ENetHost* host;
    };
    
    ENetHostEx::ENetHostEx(size_t amountOfPeer):
    m_impl(std::make_unique<Impl>())
    {
        m_impl->host = enet_host_create(ENET_ADDRESS_TYPE_IPV6, nullptr, amountOfPeer, 0, 0, 0);

        if (!m_impl->host)
            throw std::runtime_error("Failed to create enet host.");
    }

    ENetHostEx::~ENetHostEx()
    {
        if (m_impl->host)
        {
            enet_host_flush(m_impl->host);
            enet_host_destroy(m_impl->host);
        }
    }
}
