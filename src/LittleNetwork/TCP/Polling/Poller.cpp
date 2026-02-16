#include <stdexcept>
#include <LittleNetwork/TCP/Polling/Poller.hpp>
#include <LittleNetwork/TCP/Polling/Descriptor.hpp>
#include <WinSock2.h>
#include <fmt/format.h>

namespace LN
{
    Poller::Poller():
    m_descriptors()
    {
        
    }

    Poller::~Poller() = default;

    void Poller::AddDescriptor(Descriptor descriptor)
    {
        m_descriptors.emplace_back(descriptor);
    }

    void Poller::RemoveDescriptor(std::uint64_t sock)
    {
        auto it = std::find_if(m_descriptors.begin(), m_descriptors.end(), [&](const Descriptor& descriptor)
        {
            return descriptor.sock == sock;
        });

        if (it != m_descriptors.end())
        {
            m_descriptors.erase(it);
        }
    }

    bool Poller::Poll(std::int32_t timeOut)
    {
        std::vector<WSAPOLLFD> descriptors(m_descriptors.size());

        for (std::size_t i = 0; i < m_descriptors.size(); ++i)
        {
            Descriptor& descriptor = m_descriptors[i];
            WSAPOLLFD& pollFd = descriptors[i];
            pollFd.fd = descriptor.sock;
            pollFd.revents = 0;
            
            switch (descriptor.events)
            {
            case PollEvents::PollPri: pollFd.events = POLLPRI; break;
            case PollEvents::PollRdNorm: pollFd.events = POLLRDNORM; break;
            case PollEvents::PollRdBand: pollFd.events = POLLRDBAND; break;
            case PollEvents::PollIn: pollFd.events = POLLIN; break;
            case PollEvents::PollOut: pollFd.events = POLLOUT; break;
            default: throw std::runtime_error(fmt::format("Poll event type unknown!\n"));
            }
        }
        
        int activeSocketCount = WSAPoll(descriptors.data(), descriptors.size(), timeOut);

        if (activeSocketCount == SOCKET_ERROR)
        {
            throw std::runtime_error(fmt::format("Error when polling: {}\n", WSAGetLastError()));
        }
        
        if (activeSocketCount == 0)
        {
            return false;
        }

        for (std::size_t i = 0; i < m_descriptors.size(); ++i)
        {
            m_descriptors[i].revents = descriptors[i].revents;
        }

        return true;
    }

    void Poller::ForEachDescriptor(const std::function<void(const Descriptor&)>& callback)
    {
        for (const Descriptor& descriptor : m_descriptors)
        {
            callback(descriptor);
        }
    }

    Descriptor& Poller::GetDescriptorAtIndex(size_t index)
    {
        if (index >= m_descriptors.size())
        {
            throw std::runtime_error(fmt::format("Poller::GetDescriptorAtIndex: Index out of bounds!\n"));
        }

        return m_descriptors[index];
    }

    const Descriptor& Poller::GetDescriptorAtIndex(size_t index) const
    {
        if (index >= m_descriptors.size())
        {
            throw std::runtime_error(fmt::format("Poller::GetDescriptorAtIndex: Index out of bounds!\n"));
        }

        return m_descriptors[index];
    }
}
