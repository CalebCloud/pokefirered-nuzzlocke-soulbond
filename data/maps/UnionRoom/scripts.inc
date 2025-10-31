UnionRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, UnionRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, UnionRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, UnionRoom_OnFrame
	.byte 0

UnionRoom_OnFrame:
	map_script_2 VAR_TEMP_0, 0, UnionRoom_CheckSoulLinkMode
	.2byte 0

UnionRoom_CheckSoulLinkMode:
	@ Only run once per entry
	setvar VAR_TEMP_0, 1
	
	@ Check if player is in Soul-Link searching mode
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, UnionRoom_ShowSoulLinkWelcome
	end

UnionRoom_ShowSoulLinkWelcome:
	lockall
	msgbox UnionRoom_Text_SoulLinkWelcome, MSGBOX_DEFAULT
	releaseall
	end

UnionRoom_OnResume::
	@ NEW: Check if in Soul-Link mode (don't run wireless special)
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, UnionRoom_OnResume_SoulLinkMode
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 2, UnionRoom_OnResume_SoulLinkMode
	
	@ Normal Union Room behavior (wireless required)
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_1
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_2
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_3
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_4
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_5
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_6
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_7
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_8
	removeobject LOCALID_UNION_ROOM_PLAYER_1
	removeobject LOCALID_UNION_ROOM_PLAYER_2
	removeobject LOCALID_UNION_ROOM_PLAYER_3
	removeobject LOCALID_UNION_ROOM_PLAYER_4
	removeobject LOCALID_UNION_ROOM_PLAYER_5
	removeobject LOCALID_UNION_ROOM_PLAYER_6
	removeobject LOCALID_UNION_ROOM_PLAYER_7
	removeobject LOCALID_UNION_ROOM_PLAYER_8
	special RunUnionRoom
	end

UnionRoom_OnResume_SoulLinkMode:
	@ Soul-Link mode: Show debug NPC, don't run wireless special
	clearflag FLAG_HIDE_UNION_ROOM_PLAYER_1
	
	@ Hide all other players
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_2
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_3
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_4
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_5
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_6
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_7
	setflag FLAG_HIDE_UNION_ROOM_PLAYER_8
	removeobject LOCALID_UNION_ROOM_PLAYER_2
	removeobject LOCALID_UNION_ROOM_PLAYER_3
	removeobject LOCALID_UNION_ROOM_PLAYER_4
	removeobject LOCALID_UNION_ROOM_PLAYER_5
	removeobject LOCALID_UNION_ROOM_PLAYER_6
	removeobject LOCALID_UNION_ROOM_PLAYER_7
	removeobject LOCALID_UNION_ROOM_PLAYER_8
	end

UnionRoom_OnTransition::
	setvar VAR_TEMP_1, 0  @ Reset trigger flag
	end

UnionRoom_EventScript_Player1::
	lock
	faceplayer
	
	@ Check if in Soul-Link searching mode
	goto_if_ne VAR_SOUL_LINK_ACTIVE, 1, UnionRoom_Player1_NotSearching
	
	@ Offer to pair
	msgbox UnionRoom_Debug_Text_Pair, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, UnionRoom_Player1_Declined
	
	@ Accept pairing
	setvar VAR_SOUL_LINK_ACTIVE, 2
	setvar VAR_SOUL_LINK_PARTNER_ID, 12345
	msgbox UnionRoom_Debug_Text_Paired, MSGBOX_DEFAULT
	release
	end

UnionRoom_Player1_NotSearching:
	@ Check if already paired
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 2, UnionRoom_Player1_AlreadyPaired
	
	@ Not in Soul-Link mode at all
	msgbox UnionRoom_Debug_Text_NotSearching, MSGBOX_DEFAULT
	release
	end

UnionRoom_Player1_AlreadyPaired:
	@ Already paired - show status
	msgbox UnionRoom_Debug_Text_AlreadyPaired, MSGBOX_DEFAULT
	release
	end

UnionRoom_Player1_Declined:
	msgbox UnionRoom_Debug_Text_Declined, MSGBOX_DEFAULT
	release
	end

UnionRoom_EventScript_Player2::
	lock
	faceplayer
	setvar VAR_RESULT, 2
	waitstate
	release
	end

UnionRoom_EventScript_Player3::
	lock
	faceplayer
	setvar VAR_RESULT, 3
	waitstate
	release
	end

UnionRoom_EventScript_Player4::
	lock
	faceplayer
	setvar VAR_RESULT, 4
	waitstate
	release
	end

UnionRoom_EventScript_Player5::
	lock
	faceplayer
	setvar VAR_RESULT, 5
	waitstate
	release
	end

UnionRoom_EventScript_Player6::
	lock
	faceplayer
	setvar VAR_RESULT, 6
	waitstate
	release
	end

UnionRoom_EventScript_Player7::
	lock
	faceplayer
	setvar VAR_RESULT, 7
	waitstate
	release
	end

UnionRoom_EventScript_Player8::
	lock
	faceplayer
	setvar VAR_RESULT, 8
	waitstate
	release
	end

UnionRoom_EventScript_Attendant::
	lock
	faceplayer
	
	@ Check if in Soul-Link mode
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 1, UnionRoom_Attendant_SoulLinkMode
	goto_if_eq VAR_SOUL_LINK_ACTIVE, 2, UnionRoom_Attendant_SoulLinkMode
	
	@ Normal Union Room behavior
	setvar VAR_RESULT, 9
	waitstate
	release
	end

UnionRoom_Attendant_SoulLinkMode:
	@ Soul-Link mode message
	msgbox UnionRoom_Attendant_Text_SoulLinkMode, MSGBOX_DEFAULT
	release
	end

UnionRoom_EventScript_Unused::
	lockall
	setvar VAR_RESULT, 10
	waitstate
	releaseall
	end

UnionRoom_Trigger_Exit::
	@ Check if already processed this entry
	goto_if_eq VAR_TEMP_1, 1, UnionRoom_Exit_AlreadyProcessed
	
	@ Check if paired or disabled - allow passage
	goto_if_ne VAR_SOUL_LINK_ACTIVE, 1, UnionRoom_Exit_AllowPassage
	
	@ In searching mode - ask to cancel
	lockall
	msgbox UnionRoom_Text_CancelPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, UnionRoom_Exit_StayInRoom
	
	@ User chose YES - cancel Soul-Link and warp
	setvar VAR_SOUL_LINK_ACTIVE, 0
	msgbox UnionRoom_Text_SoulLinkDisabled, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkDown
	waitmovement 0
	call UnionRoom_WarpToBedroom
	end


UnionRoom_Exit_StayInRoom:
	@ User chose NO - step back and stay
	applymovement OBJ_EVENT_ID_PLAYER, Movement_StepBackFromExit
	waitmovement 0
	releaseall
	end

UnionRoom_Exit_AllowPassage:
	@ Let the warp happen normally
	setvar VAR_TEMP_1, 1
	end

UnionRoom_Exit_AlreadyProcessed:
	@ Already handled this entry, do nothing
	end

Movement_StepBackFromExit:
	walk_up
	step_end

Movement_WalkDown:
	walk_down
	step_end

UnionRoom_Trigger_ResetFlag::
	@ Reset the flag when moving away from exit
	setvar VAR_TEMP_1, 0
	end

UnionRoom_WarpToBedroom::
	fadescreen FADE_TO_BLACK
	warp MAP_PALLET_TOWN_PLAYERS_HOUSE_2F, 0
	waitstate
	end

UnionRoom_Trigger_ForceWarp::
	call UnionRoom_WarpToBedroom
	end

@ --- SOUL-LINK TEXT ---

UnionRoom_Text_SoulLinkWelcome::
	.string "Welcome to SOUL-LINK pairing!\p"
	.string "Talk to players to request\n"
	.string "a partnership.\p"
	.string "Leave through the door to cancel.$"

UnionRoom_Debug_Text_Pair::
	.string "DEBUG: Pair with test partner?$"

UnionRoom_Debug_Text_Paired::
	.string "DEBUG: Paired! You can now leave.$"

UnionRoom_Debug_Text_NotSearching::
	.string "DEBUG: Not in Soul-Link mode.$"

UnionRoom_Debug_Text_Declined::
	.string "DEBUG: Pairing declined.$"

UnionRoom_Text_CancelPrompt::
	.string "Leave without a SOUL-LINK partner?\p"
	.string "This will disable SOUL-LINK mode.$"

UnionRoom_Text_SoulLinkDisabled::
	.string "SOUL-LINK mode disabled.$"

UnionRoom_Attendant_Text_SoulLinkMode::
	.string "Welcome to the UNION ROOM!\p"
	.string "You're here to find a SOUL-LINK\n"
	.string "partner. Good luck!$"

UnionRoom_Debug_Text_AlreadyPaired::
	.string "DEBUG: Already paired!\n"
	.string "Partner ID: 12345$"
