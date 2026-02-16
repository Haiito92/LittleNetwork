#pragma once
#include <cstdint>
#include <functional>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    struct Descriptor;

    class LN_API Poller
    {
    public:
        Poller();
        Poller(const Poller& other) = delete;
        Poller(Poller&& other) = delete;
        ~Poller();
    
        Poller& operator=(const Poller& other) = delete;
        Poller& operator=(Poller&& other) = delete;

        void AddDescriptor(Descriptor descriptor);
        void RemoveDescriptor(std::uint64_t sock);

        bool Poll(std::int32_t timeOut = -1);

        void ForEachDescriptor(const std::function<void(const Descriptor&)>& callback);

        Descriptor& GetDescriptorAtIndex(size_t index);
        const Descriptor& GetDescriptorAtIndex(size_t index) const;
    private:
        std::vector<Descriptor> m_descriptors;
    };
}
