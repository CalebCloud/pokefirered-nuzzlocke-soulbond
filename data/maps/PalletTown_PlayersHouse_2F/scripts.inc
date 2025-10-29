PalletTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_PlayersHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PalletTown_PlayersHouse_2F_OnWarp
	.byte 0

PalletTown_PlayersHouse_2F_OnTransition::
	call_if_eq VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 0, PalletTown_PlayersHouse_2F_EventScript_SetRespawn
	end

PalletTown_PlayersHouse_2F_EventScript_SetRespawn::
	setrespawn HEAL_LOCATION_PALLET_TOWN
	return

PalletTown_PlayersHouse_2F_OnWarp::
	map_script_2 VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 0, PalletTown_PlayersHouse_2F_FirstWarpIn
	.2byte 0

PalletTown_PlayersHouse_2F_FirstWarpIn::
	turnobject LOCALID_PLAYER, DIR_NORTH
	setvar VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 1
	end

PalletTown_PlayersHouse_2F_EventScript_NES::
    lockall
    // Order: BOTH -> NUZ only -> SOUL only -> BOTH OFF
    goto_if_eq VAR_NUZLOCKE_ACTIVE, 1, PalletTown_PlayersHouse_2F__CheckSoulThenBoth
    goto PalletTown_PlayersHouse_2F_EventScript_NES_BothOff

PalletTown_PlayersHouse_2F__CheckSoulThenBoth:
    goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, PalletTown_PlayersHouse_2F_EventScript_NES_Both
    goto PalletTown_PlayersHouse_2F_EventScript_NES_Nuz

PalletTown_PlayersHouse_2F_EventScript_NES_Both:
    msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_Both, MSGBOX_SIGN
    releaseall
    end

PalletTown_PlayersHouse_2F_EventScript_NES_Nuz:
    msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_Nuz, MSGBOX_SIGN
    releaseall
    end

PalletTown_PlayersHouse_2F_EventScript_NES_Soul:
    msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_Soul, MSGBOX_SIGN
    releaseall
    end

PalletTown_PlayersHouse_2F_EventScript_NES_BothOff:
    // Optional: still show the normal NES flavor after the debug line
    msgbox PalletTown_PlayersHouse_2F_Text_BothOff, MSGBOX_SIGN
    msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES, MSGBOX_SIGN
    releaseall
    end

PalletTown_PlayersHouse_2F_EventScript_DebugSetModes::
    lockall
    setvar VAR_NUZLOCKE_ACTIVE, 1
    setvar VAR_SOUL_LINK_ACTIVE, 1
		giveitem ITEM_REVIVE, 5
		giveitem ITEM_MASTER_BALL, 5
    msgbox PalletTown_PlayersHouse_2F_Text_DebugModesSet, MSGBOX_SIGN
    releaseall
    end

PalletTown_PlayersHouse_2F_EventScript_Sign::
	msgbox PalletTown_PlayersHouse_2F_Text_PressLRForHelp, MSGBOX_SIGN
	end

PalletTown_PlayersHouse_2F_EventScript_PC::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	setvar VAR_0x8004, HELPCONTEXT_BEDROOM_PC
	special Script_SetHelpContext
	setvar VAR_0x8004, 1
	special AnimatePcTurnOn
	playse SE_PC_ON
	msgbox Text_PlayerBootedUpPC
	special BedroomPC
	waitstate
	special SetHelpContextForMap
	releaseall
	end

EventScript_PalletTown_PlayersHouse_2F_ShutDownPC::
	setvar VAR_0x8004, 1
	playse SE_PC_OFF
	special AnimatePcTurnOff
	special SetHelpContextForMap
	releaseall
	end
