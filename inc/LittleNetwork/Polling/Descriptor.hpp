#pragma once
#include <cstdint>
#include <LittleNetwork/Export.hpp>

namespace Ln
{
    enum class LN_API PollEvents : std::uint16_t
    {
        PollPri = 1 << 0,
        PollRdNorm = 1 << 2,
        PollRdBand = 1 << 1,	
        PollWRNorm = 1 << 3,

        PollIn = PollRdNorm | PollRdBand,
        PollOut = PollWRNorm
    };

    struct LN_API Descriptor
    {
    public:
        std::uint64_t sock;
        PollEvents events = PollEvents::PollIn;
        std::uint16_t revents = 0;
    };
}
