#pragma once

namespace Pacman
{
    enum class GhostState 
    { 
        InHouse, 
        LeavingHouse,
        GettingToHouseCenter,
        Active, 
        Frightened, 
        EatenReturning 
    };
}