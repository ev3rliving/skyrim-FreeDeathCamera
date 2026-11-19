#include "RuntimeSupport.h"
#include "HookValidation.h"
#include "OrbitHookPattern.h"
#include <array>
#include <iostream>
int main() {
    for(auto v:{Camera::Runtime::Pack(1,5,97),Camera::Runtime::Pack(1,6,1170),Camera::Runtime::Pack(1,6,1179),Camera::Runtime::Pack(1,7,99),Camera::Runtime::Pack(1,7,104)})
        if(!Camera::Runtime::Supported(v)) return 1;
    for(auto v:{Camera::Runtime::Pack(1,4,15),Camera::Runtime::Pack(1,7,105),Camera::Runtime::Pack(2,0,0)})
        if(Camera::Runtime::Supported(v)) return 2;
    std::array<std::uint8_t,128> bytes{};
    if(Camera::Pattern::FindCall(bytes)) return 3;
    const auto insert=[&](std::size_t offset) {
        std::memcpy(bytes.data()+offset,Camera::Pattern::prefix,sizeof(Camera::Pattern::prefix));
        bytes[offset+sizeof(Camera::Pattern::prefix)]=0xE8;
        std::memcpy(bytes.data()+offset+sizeof(Camera::Pattern::prefix)+5,Camera::Pattern::suffix,sizeof(Camera::Pattern::suffix));
    };
    insert(4);
    if(Camera::Pattern::FindCall(bytes)!=4+sizeof(Camera::Pattern::prefix)) return 4;
    if(Camera::Pattern::FindCall(std::span(bytes).first(20))) return 5;
    insert(64);
    if(Camera::Pattern::FindCall(bytes)) return 6;
    if(Camera::Validation::HookTarget(0,3) || Camera::Validation::Writable(0,4)) return 7;
    float value{};
    if(!Camera::Validation::Writable(reinterpret_cast<std::uintptr_t>(&value),sizeof(value))) return 8;
    auto* page=VirtualAlloc(nullptr,4096,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
    if(!page) return 9;
    std::uintptr_t target=reinterpret_cast<std::uintptr_t>(page);
    if(Camera::Validation::HookTarget(reinterpret_cast<std::uintptr_t>(&target),0)) return 10;
    DWORD old{};
    if(!VirtualProtect(page,4096,PAGE_EXECUTE_READ,&old)) return 11;
    if(!Camera::Validation::HookTarget(reinterpret_cast<std::uintptr_t>(&target),0) || Camera::Validation::Writable(target,4)) return 12;
    VirtualFree(page,0,MEM_RELEASE);
    std::cout<<"PASS runtime selection, absent/truncated/duplicate orbit signatures and memory protection checks\n";
}
