# PokéFireRed – Nuzlocke + Soul-Link + Randomizer

A comprehensive patch adding Nuzlocke, Soul-Link, and Randomizer functionality to Pokémon FireRed, complete with permadeath mechanics, white-out handling, and fully randomized encounters.

---

## Overview

This patch implements Nuzlocke rules, Soul-Link toggles, and a Wild Pokémon Randomizer for FireRed. It includes core permadeath mechanics, proper white-out handling, forced nicknaming for wild captures, and complete randomization of wild encounters and starter selection.

---

## Current Features

### Game Modes & Configuration

- **In-game configuration**: Enable Randomizer, Nuzlocke, and Soul-Link modes during Professor Oak's introduction
- **Three independent challenge modes**:
  - **Randomizer**: Completely randomizes wild Pokémon encounters and starter selection
  - **Nuzlocke**: Traditional permadeath and first-encounter rules
  - **Soul-Link**: Paired Pokémon system for two-player runs
- **Mix and match**: Enable any combination of the three modes for varied difficulty
- **Debug toggles**: Quick-enable all modes via debug tile on Player's House 2F for testing
- **Status display**: Check active modes via NES console in Player's House 2F

### Randomizer System

Complete randomization of wild Pokémon and starter selection:

- **Wild encounters**: All wild Pokémon are randomly selected from 385 valid species (Gen 1-3)
- **Starter selection**: Three random Pokémon replace Bulbasaur, Squirtle, and Charmander
  - Randomization happens once when first entering Oak's Lab
  - Same three choices persist if player declines and tries different balls
- **Rival starter**: Rival receives a random Pokémon independent from player's choices
- **Smart exclusions**: Automatically excludes Unown, invalid placeholder species (252-276), and egg species

### Permadeath System

The patch introduces a persistent per-Pokémon death flag that works across all game systems:

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
  - **No living Pokémon**: Immediate forced reset to start new run
  - **Living Pokémon available**: Player choice to continue with boxed Pokémon or reset
- **Clear prompts**: Explicit text explaining which choice continues the run vs. starting over
- **Updated defeat text**: Vanilla messages updated to acknowledge Nuzlocke consequences
- **On-screen notices**: Additional warnings during white-out sequence

### First Rival Battle

- Early rival battle defeat now properly triggers Nuzlocke white-out logic
- No more forgiving vanilla behavior on the first loss

---

## Current Behavior Summary

1. **During Oak's intro**: Player chooses whether to enable Randomizer, Nuzlocke, and Soul-Link modes
2. **Starter selection**: 
   - With Randomizer: Three random Pokémon appear (fixed for that playthrough)
   - Without Randomizer: Normal Bulbasaur/Squirtle/Charmander selection
3. **Wild encounters**: 
   - With Randomizer: Every wild Pokémon is randomly selected
   - Without Randomizer: Normal encounter tables apply
4. **During battle**: Any Pokémon fainting under Nuzlocke rules is permanently marked as dead
5. **Wild Capture & Starters**: Under Nuzlocke, player is forced to provide a unique nickname (cannot be empty, whitespace-only, or species name)
6. **On white-out**:
   - System automatically checks PC boxes for living Pokémon
   - If none exist → Automatic reset to new run
   - If survivors exist → Player chooses to continue with boxed team or reset
7. **First rival loss**: Uses same white-out router as regular defeats (no special treatment)

---

## Known Limitations & Planned Improvements

### Critical: Mode Persistence Issue

**Current**: Game mode selections (Randomizer/Nuzlocke/Soul-Link) are not persisted after Oak's intro sequence  
**Workaround**: Use debug tile in Player's House 2F to re-enable modes after loading saves  
**Needed**: Proper flag/variable persistence system that survives the intro sequence

### Rival Battle Randomization

**Current**: Rival's first battle team still uses default starter (not randomized)  
**Needed**: Modify rival trainer battle data to use randomized species

### NPC Trainer Randomization

**Current**: Only wild Pokémon and player/rival starters are randomized  
**Not implemented**: NPC trainer teams remain unchanged

### New-Run Reset Routine

**Current**: Stub implementation  
**Needed**: Full reset system that:

- ✅ Preserves: Player name, rival name, Nuzlocke toggle, Soul-Link toggle, Soul-Link partner ID
- ❌ Wipes: Party, PC boxes, money, bag contents, key items, Pokédex, badges, story flags, event flags, temporary variables, map visit state
- 🎯 Respawns player in Player's House 2F (pre-starter selection)
- 💾 Sets appropriate respawn point and performs clean save

### Route Encounter Locks

- Enforce first-encounter-only rules per route/area

### Nickname Enforcement

- Doesn't yet apply to trades or in game gifts like your starter, only wild pokemon
