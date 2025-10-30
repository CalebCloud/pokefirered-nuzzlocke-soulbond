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
	
	@ Check all three flags: Nuzlocke, Soul Link, and Randomizer
	@ We'll build a composite message based on what's enabled
	
	@ First check if Nuzlocke is on
	goto_if_eq VAR_NUZLOCKE_ACTIVE, 1, PalletTown_PlayersHouse_2F_CheckSoulAndRandom
	
	@ Nuzlocke is OFF, check if Soul Link is on (edge case, but handle it)
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, PalletTown_PlayersHouse_2F_CheckRandomOnly_SoulOn
	
	@ Both Nuzlocke and Soul Link are OFF, check randomizer only
	checkflag FLAG_WILD_RANDOMIZER_ENABLED
	goto_if 1, PalletTown_PlayersHouse_2F_EventScript_NES_RandomOnly
	
	@ All three are OFF
	goto PalletTown_PlayersHouse_2F_EventScript_NES_AllOff

PalletTown_PlayersHouse_2F_CheckSoulAndRandom:
	@ Nuzlocke is ON, check Soul Link
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, PalletTown_PlayersHouse_2F_CheckRandom_BothOn
	
	@ Nuzlocke ON, Soul Link OFF, check randomizer
	checkflag FLAG_WILD_RANDOMIZER_ENABLED
	goto_if 1, PalletTown_PlayersHouse_2F_EventScript_NES_NuzRandom
	
	@ Only Nuzlocke is ON
	goto PalletTown_PlayersHouse_2F_EventScript_NES_NuzOnly

PalletTown_PlayersHouse_2F_CheckRandom_BothOn:
	@ Both Nuzlocke and Soul Link are ON, check randomizer
	checkflag FLAG_WILD_RANDOMIZER_ENABLED
	goto_if 1, PalletTown_PlayersHouse_2F_EventScript_NES_AllThree
	
	@ Nuzlocke + Soul Link only (no randomizer)
	goto PalletTown_PlayersHouse_2F_EventScript_NES_NuzSoul

PalletTown_PlayersHouse_2F_CheckRandomOnly_SoulOn:
	@ Soul Link ON (Nuzlocke OFF), check randomizer
	checkflag FLAG_WILD_RANDOMIZER_ENABLED
	goto_if 1, PalletTown_PlayersHouse_2F_EventScript_NES_SoulRandom
	
	@ Only Soul Link is ON
	goto PalletTown_PlayersHouse_2F_EventScript_NES_SoulOnly

@ ===== MESSAGE DISPLAY SCRIPTS =====

PalletTown_PlayersHouse_2F_EventScript_NES_AllThree:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_AllThree, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_NuzSoul:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_NuzSoul, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_NuzRandom:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_NuzRandom, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_SoulRandom:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_SoulRandom, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_NuzOnly:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_Nuz, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_SoulOnly:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_Soul, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_RandomOnly:
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES_RandomOnly, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_NES_AllOff:
	msgbox PalletTown_PlayersHouse_2F_Text_AllOff, MSGBOX_SIGN
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES, MSGBOX_SIGN
	releaseall
	end

PalletTown_PlayersHouse_2F_EventScript_DebugSetModes::
	lockall
	setvar VAR_NUZLOCKE_ACTIVE, 1
	setvar VAR_SOUL_LINK_ACTIVE, 1
	setflag FLAG_WILD_RANDOMIZER_ENABLED
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
