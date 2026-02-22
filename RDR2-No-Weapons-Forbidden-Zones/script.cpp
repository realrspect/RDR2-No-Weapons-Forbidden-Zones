#include "script.h"

// To get rid of the zone in the wapiti reservation, we're forcing a cleanup of the wapiti script every frame which essentially kills it.
// This removes the zone and does not seem to break anything else. Peds still spawn, and they actually have special voice lines if you threaten them.
int g_cleanupFlags = 523;

static void AllowWeaponsInWapiti()
{
    bool isEpilogueActive = MISSIONDATA::MISSIONDATA_WAS_COMPLETED(MISC::GET_HASH_KEY("FIN1"));

    if (!isEpilogueActive)
    {
        PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("wapiti", g_cleanupFlags);

        if (MAP::_MAP_IS_REGION_HIGHLIGHTED_WITH_STYLE(MISC::GET_HASH_KEY("REGION_GRZ_WAPITI"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION")))
        {
            MAP::_MAP_DISABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_GRZ_WAPITI"));
        }
    }
}

static void AllowWeaponsInRhodes()
{
    UINT64* g_EnableRhodesRestrictions = getGlobalPtr(1835011 + 1 + (16 * 74) + 1); // The global variable that controls the restrictions in Rhodes / Caliga Hall.

    Hash TheNewSouth = MISC::GET_HASH_KEY("FUD1");
    Hash AShortWalkInAPrettyTown = MISC::GET_HASH_KEY("GRY3");

    if (MISSIONDATA::MISSIONDATA_WAS_COMPLETED(TheNewSouth) && !MISSIONDATA::MISSIONDATA_WAS_COMPLETED(AShortWalkInAPrettyTown))
    {
        *g_EnableRhodesRestrictions = false;

        // Only remove necessary blip style.
        if (MAP::_MAP_IS_REGION_HIGHLIGHTED_WITH_STYLE(MISC::GET_HASH_KEY("REGION_SCM_RHODES"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION")))
        {
            MAP::_MAP_DISABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_SCM_RHODES"));
        }

        if (MAP::_MAP_IS_REGION_HIGHLIGHTED_WITH_STYLE(MISC::GET_HASH_KEY("REGION_SCM_CALIGAHALL"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION")))
        {
            MAP::_MAP_DISABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_SCM_CALIGAHALL"));
        }
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
    UINT64* g_EnableRhodesRestrictions = getGlobalPtr(1835011 + 1 + (16 * 74) + 1);     

    Hash TheNewSouth = MISC::GET_HASH_KEY("FUD1");
    Hash AShortWalkInAPrettyTown = MISC::GET_HASH_KEY("GRY3");
    bool isEpilogueActive = MISSIONDATA::MISSIONDATA_WAS_COMPLETED(MISC::GET_HASH_KEY("FIN1"));

    if (MISSIONDATA::MISSIONDATA_WAS_COMPLETED(TheNewSouth) && !MISSIONDATA::MISSIONDATA_WAS_COMPLETED(AShortWalkInAPrettyTown))
    {
        *g_EnableRhodesRestrictions = true;
        
        MAP::_MAP_ENABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_SCM_RHODES"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION"));
        MAP::_MAP_ENABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_SCM_CALIGAHALL"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION"));

        PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("rhodes", g_cleanupFlags);
        PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("caligahall", g_cleanupFlags);
    }

    if (!isEpilogueActive)
    {
        MAP::_MAP_ENABLE_REGION_BLIP(MISC::GET_HASH_KEY("REGION_GRZ_WAPITI"), MISC::GET_HASH_KEY("BLIP_STYLE_SELECTED_REGION"));

        PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("wapiti", g_cleanupFlags);
    }
}
