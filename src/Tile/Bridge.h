#ifndef BRIDGE_H
#define BRIDGE_H

#include "Boat.h"


struct Bridge
{
    // when the Infos are given
    bool giveInfoToFight;
    bool giveInfoToTile;

    // Infos Fight need

    // Infos Tile need
    int typeBoatKept; // If you can choose either to keep your boat or to get the ennemies boat


    // both
    Boat* ennemyBoat;
    Boat* playerBoat;
};

Bridge initBridge();


#endif
