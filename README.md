# PokéFireRed – Nuzlocke + Soul-Link + Randomizer

A comprehensive patch adding Nuzlocke, Soul-Link, and Randomizer functionality to Pokémon FireRed, complete with permadeath mechanics, white-out handling, fully randomized encounters, and first-encounter-per-route enforcement.

---

## Overview

This patch implements Nuzlocke rules, Soul-Link toggles, and a Wild Pokémon Randomizer for FireRed. It includes core permadeath mechanics, proper white-out handling, forced nicknaming for wild captures, complete randomization of wild encounters and starter selection, and classic Nuzlocke first-encounter-per-route enforcement.

---

## Current Features

### Game Modes & Configuration

- **In-game configuration**: Enable Randomizer, Nuzlocke, and Soul-Link modes during Professor Oak's introduction
- **Three independent challenge modes**:
  - **Randomizer**: Completely randomizes wild Pokémon encounters and starter selection
  - **Nuzlocke**: Traditional permadeath and first-encounter-per-route rules
  - **Soul-Link**: Paired Pokémon system for two-player runs
- **Mix and match**: Enable any combination of the three modes for varied difficulty
- **Debug toggles**: Quick-enable all modes via debug tile on Player's House 2F for testing
- **Status display**: Check active modes via NES console in Player's House 2F
- **Persistent settings**: Challenge mode choices survive game initialization and save/load

### Randomizer System

Complete randomization of wild Pokémon and starter selection:

- **Wild encounters**: All wild Pokémon are randomly selected from 385 valid species (Gen 1-3)
- **Starter selection**: Three random Pokémon replace Bulbasaur, Squirtle, and Charmander
  - Randomization happens once when first entering Oak's Lab
  - Same three choices persist if player declines and tries different balls
  - Starters re-randomize on Nuzlocke reset for fresh runs
- **Rival starter**: Rival receives a random Pokémon independent from player's choices
- **Smart exclusions**: Automatically excludes Unown (201), invalid placeholder species (252-276), and egg species (412)
- **No `??` Pokémon**: Robust validation ensures only valid species appear

### Nuzlocke First Encounter System

Classic Nuzlocke route encounter enforcement with intelligent activation:

- **Delayed activation**: First encounter tracking begins only after receiving Poké Balls from Oak
  - Before Poké Balls: Wild encounters happen normally without tracking
  - After receiving Poké Balls: Message displays "Your Nuzlocke Challenge has begun!"
  - From this point forward, first encounters are tracked per route/area
- **Per-route tracking**: Automatic flag system tracks first encounter in each of 256 possible areas
  - Uses map section ID for dynamic route identification
  - Route 1, Route 2, Viridian Forest, etc. each get independent tracking
- **Catch blocking**: After first encounter on a route, attempting to throw a Poké Ball shows:
  - Blocked ball animation (same as trainer battles)
  - Message: "You've already caught a POKéMON on this route!"
  - Can still battle, flee, or defeat wild Pokémon—just can't catch
- **Reset behavior**: On Nuzlocke reset, all route flags clear for fresh run

### Nuzlocke Reset System

Full game reset with selective preservation:

- **Automatic on wipe**: When all Pokémon are dead, automatic reset after white-out
- **Optional with survivors**: Choice to reset or continue if living Pokémon exist in PC
- **Preserves**:
  - Player name
  - Rival name
  - Randomizer setting
  - Nuzlocke mode setting
  - Soul-Link mode setting
- **Wipes**:
  - Party and PC boxes
  - Money (resets to ₽3000)
  - Bag contents and key items
  - Pokédex data
  - Badges and story progress
  - All event flags (including route encounter flags)
  - First encounter tracking (must get Poké Balls again)
- **Fresh start**: Spawns in bedroom, ready to get new starter with re-randomized options

### Permadeath System

Persistent per-Pokémon death flag that works across all game systems:

- **Automatic marking**: Player Pokémon are permanently marked as dead when they faint under Nuzlocke rules
- **Comprehensive restrictions** for dead Pokémon:
  - Remain at 0 HP when retrieved from PC storage
  - Excluded from all healing and PP restoration
  - Cannot be revived with items or services
  - Display clear **DEAD** tag in party UI and summary screens
  - Menu interactions limited to safe actions (e.g., Summary only)

### Nickname Enforcement (Wild Captures & Starters)

- **Required Nicknames**: Players are forced to nickname captured wild Pokémon and starters under Nuzlocke rules
  - Skips the "Give nickname?" prompt entirely
- **Validation**: Blocks empty names, names consisting only of spaces, and names identical to the species' name (including leading/trailing spaces)

### White-Out Handling

Complete overhaul of the defeat system with Nuzlocke-aware logic:

- **Dual entry points**: Separate flows for Pokémon Center and Home (Mom) variants
- **Living Pokémon detection**: Automatically scans PC boxes for survivors
- **Smart routing**:
  - **No living Pokémon**: Immediate forced reset with preserved challenge modes
  - **Living Pokémon available**: Player choice to continue with boxed Pokémon or reset
- **Clear prompts**: Explicit text explaining which choice continues the run vs. starting over
- **Updated defeat text**: Vanilla messages updated to acknowledge Nuzlocke consequences
- **On-screen notices**: Additional warnings during white-out sequence

### First Rival Battle

- Early rival battle defeat properly triggers Nuzlocke white-out logic
- No more forgiving vanilla behavior on the first loss

---

## Current Behavior Summary

1. **During Oak's intro**: Player chooses whether to enable Randomizer, Nuzlocke, and Soul-Link modes
2. **Settings persist**: Challenge mode selections survive through game initialization and save/load cycles
3. **Starter selection**: 
   - With Randomizer: Three random Pokémon appear (fixed for that playthrough)
   - Without Randomizer: Normal Bulbasaur/Squirtle/Charmander selection
4. **Receive Poké Balls**: Oak gives 5 Poké Balls after delivering parcel
   - If Nuzlocke enabled: "Your Nuzlocke Challenge has begun!" message displays
   - First encounter tracking activates from this point forward
5. **Wild encounters**: 
   - With Randomizer: Every wild Pokémon is randomly selected from 385 valid species
   - Without Randomizer: Normal encounter tables apply
6. **First encounter per route**: 
   - First wild encounter on each route: Can catch normally
   - Subsequent encounters on same route: Poké Ball is blocked with message
   - Different routes: Fresh first encounter available
7. **During battle**: Any Pokémon fainting under Nuzlocke rules is permanently marked as dead
8. **Wild Capture & Starters**: Under Nuzlocke, player is forced to provide a unique nickname
9. **On white-out**:
   - System automatically checks PC boxes for living Pokémon
   - If none exist → Full reset preserving names and challenge modes
   - If survivors exist → Player chooses to continue with boxed team or reset
   - Reset wipes everything except names and challenge mode flags
   - Starters are re-randomized and route flags cleared for the new run
10. **First rival loss**: Uses same white-out router as regular defeats

---

## Known Limitations & Planned Improvements

### Minor: Poké Ball Consumption on Blocked Catch

**Current**: When attempting to catch on a "used" route, the Poké Ball is consumed even though catch is blocked  
**Impact**: Minor resource waste, but provides feedback that route is already used  
**Planned**: Investigate preventing ball consumption on blocked attempts

### Rival Battle Randomization

**Current**: Rival's first battle team still uses default starter (not randomized)  
**Needed**: Modify rival trainer battle data to use randomized species from `RIVAL_STARTER_SPECIES`

### NPC Trainer Randomization

**Current**: Only wild Pokémon and player/rival starters are randomized  
**Not implemented**: NPC trainer teams remain unchanged

### Advanced Nuzlocke Rules

**Not implemented**: Optional variants like:
- Shiny clause (allow catching shinies even on used routes)
- Dupes clause (re-roll if first encounter is duplicate of owned species)
- Separate encounter slots for fishing/surfing vs grass
- Gift Pokémon and static encounter handling

### Nickname Enforcement for Trades/Gifts

**Current**: Forced nicknaming only applies to wild captures and starter selection  
**Not implemented**: In-game trades and gift Pokémon don't enforce nicknames under Nuzlocke

---

## Technical Implementation Notes

### Flag System
- `FLAG_NUZLOCKE_ENCOUNTERS_ACTIVE (0x200)`: Master switch set when Oak gives Poké Balls
- `FLAG_NUZLOCKE_TEMP_BLOCK_CATCH (0x4FE)`: Temporary battle flag signaling "catch blocked"
- `FLAG_NUZLOCKE_ROUTE_BASE (0x900-0x9FF)`: 256 dynamic route flags, auto-assigned by map section ID