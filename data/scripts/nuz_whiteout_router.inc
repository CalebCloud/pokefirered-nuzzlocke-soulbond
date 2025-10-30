@ data/scripts/nuz_whiteout_router.inc
@ Router called after white-out fade, instead of the vanilla script.
@ Two variants: Center vs Home (Mom), matching your C jump sites.

EventScript_Nuz_AfterWhiteOut_ToCenter_Router::
    @ If Nuzlocke OFF -> vanilla
    goto_if_ne VAR_NUZLOCKE_ACTIVE, 1, EventScript_AfterWhiteOutHeal

    @ Nuz ON -> do we have any living mons in PC?
    special Special_Nuz_PCHasLivingMons
    goto_if_eq VAR_RESULT, 0, EventScript_Nuz_ForceReset   @ none -> forced reset

    @ There are living mons -> ask
    lockall
    msgbox Nuz_Text_ContinueOrReset, MSGBOX_YESNO  @ YES = New run, NO = Continue
    goto_if_eq VAR_RESULT, 1, EventScript_Nuz_Continue_Center  @ NO -> continue
    releaseall
    goto EventScript_Nuz_ResetRun

EventScript_Nuz_Continue_Center:
    releaseall
    goto EventScript_AfterWhiteOutHeal  @ vanilla heal script

@ --- "Home (Mom)" variant ---
EventScript_Nuz_AfterWhiteOut_ToHome_Router::
    @ If Nuzlocke OFF -> vanilla
    goto_if_ne VAR_NUZLOCKE_ACTIVE, 1, EventScript_AfterWhiteOutMomHeal

    special Special_Nuz_PCHasLivingMons
    goto_if_eq VAR_RESULT, 0, EventScript_Nuz_ForceReset

    lockall
    msgbox Nuz_Text_ContinueOrReset, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, 1, EventScript_Nuz_Continue_Home  @ NO -> continue
    releaseall
    goto EventScript_Nuz_ResetRun

EventScript_Nuz_Continue_Home:
    releaseall
    goto EventScript_AfterWhiteOutMomHeal

@ --- Forced reset path (no living boxed mons) ---
EventScript_Nuz_ForceReset:
    lockall
    msgbox Nuz_Text_NoMonsForceReset, MSGBOX_DEFAULT
    releaseall
    goto EventScript_Nuz_ResetRun

@ --- FULL RESET ROUTINE ---
@ Preserves: Player name, rival name, challenge mode flags (Randomizer/Nuzlocke/Soul-Link)
@ Wipes: Party, PC boxes, money, bag, key items, Pokédex, badges, story flags, etc.
EventScript_Nuz_ResetRun:
    lockall
    msgbox Nuz_Text_ResettingRun, MSGBOX_DEFAULT
    closemessage
    
    @ Perform the full game reset (preserves names and challenge modes)
    special Special_NuzlockeResetRun
    
    @ Now manually set the warp since we're in script context
    setrespawn HEAL_LOCATION_PALLET_TOWN
    warp MAP_PALLET_TOWN_PLAYERS_HOUSE_2F, 255, 6, 6
    waitstate
    releaseall
    end

@ --- Text ---
Nuz_Text_ContinueOrReset::
    .string "You blacked out.\p"
    .string "Continue Nuzlocke run with\n"
    .string "living PC Pokémon?\p"
    .string "YES = Continue\n"
    .string "NO  = Reset run.$"

Nuz_Text_NoMonsForceReset::
    .string "You have no living POKéMON\n"
    .string "left in your PC.\p"
    .string "Starting a NEW RUN now.$"

Nuz_Text_ResettingRun::
    .string "Resetting your adventure...\p"
    .string "Your challenge modes remain active!\n"
    .string "Good luck on your new run!$"