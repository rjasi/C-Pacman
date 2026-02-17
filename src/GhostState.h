#pragma once

namespace Pacman
{
    enum class GhostState 
    { 
        Chase = 0, 
        Frightened,
        Scatter, 
        EatenReturning 
    };

    enum class HouseState 
    { 
        InHouse, 
        LeavingGettingToHouseCenter, 
        Exiting,
        Outside,
        EnteringGettingToHouseCenter,
        GettingToCorner,
    };
}