# C-Pacman
Pacman in C++ with SFML


# TODO
1. thread safe logger
2. handle loading errors
3. class for handling loading from file? 

# Pathfinding for ghosts 
Pathfinding for ghosts is split into 2 classes using the strategy pattern
class IGhostTargetStrategy determines where a ghost should go
class IPathingStrategy determines how to actually get where IGhostTargetStrategy tells

