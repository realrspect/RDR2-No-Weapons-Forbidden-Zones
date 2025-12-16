#include "script.h"

// To get rid of the zone in the wapiti reservation, we're forcing a cleanup of the wapiti script every frame which essentially kills it.
// This removes the zone and does not seem to break anything else. Peds still spawn, and they actually have special voice lines if you threaten them.
static void AllowWeaponsInWapiti()
{
    int cleanupFlags = 523; // You can get these cleanup flags by going through the script you'd like to terminate and checking which number gets passed into PLAYER::HAS_FORCE_CLEANUP_OCCURRED.

    PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("wapiti", cleanupFlags);

    // Removes the white region blip from the map
    MAP::_MAP_DISABLE_REGION_BLIP(0xBB785C8A); // REGION_GRZ_WAPITI
}

static void AllowWeaponsInRhodes()
{
    Hash TheNewSouth = MISC::GET_HASH_KEY("FUD1");
    Hash AShortWalkInAPrettyTown = MISC::GET_HASH_KEY("GRY3");

    // I didn't notice any bugs or unwanted behavior while testing, but just to make sure, 
    // we're only changing this global if the game is between the mission where the restriction gets created and where it's removed.
    if (MISSIONDATA::MISSIONDATA_WAS_COMPLETED(TheNewSouth) && !MISSIONDATA::MISSIONDATA_WAS_COMPLETED(AShortWalkInAPrettyTown))
    {
        // Changing this global to zero effectively disables the restriction zone in both Rhodes and Caliga Hall.
        // Setting it to 1 re-enables it, even if the game is not in chapter 3.
        *getGlobalPtr(1835011 + 1 + (16 * 74) + 1) = 0; // Global_1835011[iParam0 /*74*/].f_1

        // Removes the white region blip from the map
        MAP::_MAP_DISABLE_REGION_BLIP(0xD3F2B8A7); // REGION_SCM_RHODES
        MAP::_MAP_DISABLE_REGION_BLIP(0xD218D90D); // REGION_SCM_CALIGAHALL
    }
}

void ScriptMain()
{
    while (true)
    {
        AllowWeaponsInWapiti();
        AllowWeaponsInRhodes();
        WAIT(0);
    }

}
