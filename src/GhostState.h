#pragma once

namespace Pacman
{
    enum class GhostState 
    { 
        InHouse = 0, 
        LeavingHouse,
        GettingToHouseCenter,
        Chase, 
        Frightened,
        Scatter, 
        EatenReturning 
    };
}