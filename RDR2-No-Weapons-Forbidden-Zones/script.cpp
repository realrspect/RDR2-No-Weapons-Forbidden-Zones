#include "script.h"

// To get rid of the zone in the wapiti reservation, we're forcing a cleanup of the wapiti script every frame which essentially kills it.
// This removes the zone and does not seem to break anything else. Peds still spawn, and they actually have special voice lines if you threaten them.
static void AllowWeaponsInWapiti()
{
    bool isEpilogueActive = MISSIONDATA::MISSIONDATA_WAS_COMPLETED(MISC::GET_HASH_KEY("FIN1"));

    if (!isEpilogueActive)
    {
        int cleanupFlags = 523;

        PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("wapiti", cleanupFlags);

        MAP::_MAP_DISABLE_REGION_BLIP(0xBB785C8A);
    }
}

static void AllowWeaponsInRhodes()
{
    Hash TheNewSouth = MISC::GET_HASH_KEY("FUD1");
    Hash AShortWalkInAPrettyTown = MISC::GET_HASH_KEY("GRY3");
    UINT64* g_Chapter3RestrictionsActive = getGlobalPtr(1835011 + 1 + (16 * 74) + 1);     

    if (MISSIONDATA::MISSIONDATA_WAS_COMPLETED(TheNewSouth) && !MISSIONDATA::MISSIONDATA_WAS_COMPLETED(AShortWalkInAPrettyTown))
    {
        *g_Chapter3RestrictionsActive = false;

        MAP::_MAP_DISABLE_REGION_BLIP(0xD3F2B8A7);
        MAP::_MAP_DISABLE_REGION_BLIP(0xD218D90D);   
    }
}

void ScriptAttach()
{
    while (true)
    {
        AllowWeaponsInWapiti();
        AllowWeaponsInRhodes();
        WAIT(0);
    }
}

void ScriptDetach()
{
    Hash TheNewSouth = MISC::GET_HASH_KEY("FUD1");
    Hash AShortWalkInAPrettyTown = MISC::GET_HASH_KEY("GRY3");
    UINT64* g_Chapter3RestrictionsActive = getGlobalPtr(1835011 + 1 + (16 * 74) + 1);
    bool isEpilogueActive = MISSIONDATA::MISSIONDATA_WAS_COMPLETED(MISC::GET_HASH_KEY("FIN1"));

    if (MISSIONDATA::MISSIONDATA_WAS_COMPLETED(TheNewSouth) && !MISSIONDATA::MISSIONDATA_WAS_COMPLETED(AShortWalkInAPrettyTown))
    {
        *g_Chapter3RestrictionsActive = true;
        
        MAP::_MAP_ENABLE_REGION_BLIP(0xD3F2B8A7, MISC::GET_HASH_KEY("BLIP_STYLE_FRIENDLY"));
        MAP::_MAP_ENABLE_REGION_BLIP(0xD218D90D, MISC::GET_HASH_KEY("BLIP_STYLE_FRIENDLY"));
    }

    if (!isEpilogueActive)
    {
        MAP::_MAP_ENABLE_REGION_BLIP(0xBB785C8A, MISC::GET_HASH_KEY("BLIP_STYLE_FRIENDLY"));
    }
}