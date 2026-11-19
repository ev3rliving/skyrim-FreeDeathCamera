#pragma once
#include <cstdint>
#include <cstring>
#include <optional>
#include <span>
namespace Camera::Pattern {
inline constexpr std::uint8_t prefix[]{0xFF,0xC6,0x41,0xB0,0x01,0x48,0x8D,0x53,0x40,0x48,0x8B,0x4B,0x10};
inline constexpr std::uint8_t suffix[]{0x84,0xC0,0x0F,0x85};
// No patch for an absent, truncated or ambiguous instruction sequence.
inline std::optional<std::size_t> FindCall(std::span<const std::uint8_t> bytes) {
    // Include the four-byte displacement after the trailing near-JNE opcode.
    constexpr auto size=sizeof(prefix)+5+sizeof(suffix)+4;
    std::optional<std::size_t> found;
    for(std::size_t i=0;i+size<=bytes.size();++i) {
        if(std::memcmp(bytes.data()+i,prefix,sizeof(prefix))==0 &&
            bytes[i+sizeof(prefix)]==0xE8 &&
            std::memcmp(bytes.data()+i+sizeof(prefix)+5,suffix,sizeof(suffix))==0) {
            if(found) return std::nullopt;
            found=i+sizeof(prefix);
        }
    }
    return found;
}
}
