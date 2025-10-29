# PokéFireRed – Nuzlocke + Soul-Link

A comprehensive patch adding Nuzlocke and Soul-Link functionality to Pokémon FireRed, complete with permadeath mechanics, white-out handling, and early-game flow improvements.

---

## Overview

This patch implements first-pass Nuzlocke rules and Soul-Link toggles for FireRed. It includes core permadeath mechanics, proper white-out handling, and the groundwork for a full Nuzlocke experience.

---

## Current Features

### Nuzlocke/Soul-Link Setup

- **In-game configuration**: Enable Nuzlocke and Soul-Link modes during Professor Oak's introduction
- **Debug toggles**: Quick-enable both modes via a temporary debug sign on Player's House 2F for testing purposes

### Permadeath System

The patch introduces a persistent per-Pokémon death flag that works across all game systems:

- **Automatic marking**: Player Pokémon are permanently marked as dead when they faint under Nuzlocke rules
- **Comprehensive restrictions** for dead Pokémon:
  - Remain at 0 HP when retrieved from PC storage
  - Excluded from all healing and PP restoration
  - Cannot be revived with items or services
  - Display clear **DEAD** tag in party UI and summary screens
  - Menu interactions limited to safe actions (e.g., Summary only)

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

1. **During battle**: Any Pokémon fainting under Nuzlocke rules is permanently marked as dead
2. **On white-out**:
   - System automatically checks PC boxes for living Pokémon
   - If none exist → Automatic reset to new run
   - If survivors exist → Player chooses to continue with boxed team or reset
3. **First rival loss**: Uses same white-out router as regular defeats (no special treatment)

---

## Known Limitations & Planned Improvements

### Critical: New-Run Reset Routine

**Current**: Stub implementation  
**Needed**: Full reset system that:

- ✅ Preserves: Player name, rival name, Nuzlocke toggle, Soul-Link toggle, Soul-Link partner ID
- ❌ Wipes: Party, PC boxes, money, bag contents, key items, Pokédex, badges, story flags, event flags, temporary variables, map visit state
- 🎯 Respawns player in Player's House 2F (pre-starter selection)
- 💾 Sets appropriate respawn point and performs clean save

### Intro Dialog State Gets Reset

Temporary variables and flags from Oak's Nuzlocke/Soul-Link questions need to be persisted.
- They are currently cleared immediately after onboarding


### Route Encounter Locks

- Enforce first-encounter-only rules per route/aread

### Nickname Enforcement

- Require nickname entry on all captures under Nuzlocke rules
- Block empty name submissions
- Apply to both wild captures and in-game trades