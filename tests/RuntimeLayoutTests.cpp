#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <iostream>
int main() {
    alignas(RE::PlayerCharacter) std::byte actorStorage[sizeof(RE::PlayerCharacter)+1024]{};
    auto* actor=reinterpret_cast<RE::PlayerCharacter*>(actorStorage);
    alignas(RE::PlayerCamera) std::byte cameraStorage[sizeof(RE::PlayerCamera)+64]{};
    auto* camera=reinterpret_cast<RE::PlayerCamera*>(cameraStorage);
    for(const auto v:{REL::Version{1,5,97,0},REL::Version{1,6,1170,0},REL::Version{1,6,1179,0},REL::Version{1,7,99,0},REL::Version{1,7,104,0}}) {
        if(!REL::Module::mock(v)) return 1;
        const bool ae=v>=REL::Version{1,6,0,0};
        if(REL::Module::IsAE()!=ae || REL::RelocationID(11,22).id()!=(ae?22:11)) return 2;
        if(reinterpret_cast<std::uintptr_t>(actor->AsActorState())-reinterpret_cast<std::uintptr_t>(actor)!=(ae?0xC0:0xB8)) return 3;
        if(reinterpret_cast<std::uintptr_t>(&camera->GetRuntimeData().cameraStates)-reinterpret_cast<std::uintptr_t>(camera)!=0xB8) return 4;
        std::cout<<v.string()<<" runtime selection, actor-state accessor and camera array offset passed\n";
    }
    REL::Module::reset();
}
