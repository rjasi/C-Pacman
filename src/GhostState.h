#pragma once

namespace Pacman
{
    enum class GhostState 
    { 
        InHouse, 
        LeavingHouse,
        GettingToHouseCenter,
        Chase, 
        Frightened,
        Scatter, 
        EatenReturning 
    };
}