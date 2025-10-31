# PokéFireRed – Nuzlocke + Soul-Link + Randomizer

A comprehensive patch adding Nuzlocke, Soul-Link, and Randomizer functionality to Pokémon FireRed, complete with permadeath mechanics, white-out handling, fully randomized encounters, first-encounter-per-route enforcement, and wireless multiplayer Soul-Link pairing.

---

## Overview

This patch implements Nuzlocke rules, Soul-Link co-op challenges, and a Wild Pokémon Randomizer for FireRed. It includes core permadeath mechanics, proper white-out handling, forced nicknaming for wild captures, complete randomization of wild encounters and starter selection, classic Nuzlocke first-encounter-per-route enforcement, and a Union Room pairing system for two-player Soul-Link runs.

---

## Current Features

### Game Modes & Configuration

- **In-game configuration**: Enable Randomizer, Nuzlocke, and Soul-Link modes during Professor Oak's introduction
- **Three independent challenge modes**:
  - **Randomizer**: Completely randomizes wild Pokémon encounters and starter selection
  - **Nuzlocke**: Traditional permadeath and first-encounter-per-route rules
  - **Soul-Link**: Paired Pokémon system for two-player runs (Phase 1: Debug pairing complete)
- **Mix and match**: Enable any combination of the three modes for varied difficulty
- **Debug toggles**: Quick-enable all modes via debug tile on Player's House 2F for testing
- **Status display**: Check active modes via NES console in Player's House 2F
- **Persistent settings**: Challenge mode choices survive game initialization, save/load, and Nuzlocke resets

### Soul-Link System (Phase 1: Solo Debug Mode - COMPLETE)

Union Room pairing system with debug NPC for testing:

- **Spawn behavior**: Players who enable Soul-Link during Oak's intro spawn in Union Room instead of bedroom
- **Solo pairing mode**: Debug NPC (Player 1) allows testing pairing mechanics without wireless connection
- **Union Room mechanics**:
  - Welcome message explains pairing system
  - Talk to debug NPC to request pairing
  - Accept pairing → Soul-Link activated (VAR_SOUL_LINK_ACTIVE = 2)
  - Paired players can exit through any of 3 door tiles
  - Cancel Soul-Link option when leaving without partner
- **Exit triggers**: Three-tile-wide exit system prevents bypassing prompts
- **Partner persistence**: Partner ID (12345 in debug) preserved across Nuzlocke resets
- **NES status display**: Shows "SOUL-LINK: PAIRED (ID: 12345)" after successful pairing
- **Elevation fixes**: All collision/layer bugs resolved using elevation 0 uniformly
- **No wireless requirement**: Bypasses `special RunUnionRoom` when in Soul-Link mode

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
  - Soul-Link mode setting and partner ID (if paired)
- **Wipes**:
  - Party and PC boxes
  - Money (resets to ₽3000)
  - Bag contents and key items
  - Pokédex data
  - Badges and story progress
  - All event flags (including route encounter flags)
  - First encounter tracking (must get Poké Balls again)
- **Fresh start**: Spawns in bedroom, ready to get new starter with re-randomized options
- **Soul-Link integration**: Paired status preserved across resets for synchronized runs

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
3. **Soul-Link spawn**: Players who enable Soul-Link spawn in Union Room for pairing
   - Debug NPC available for solo testing
   - Accept pairing → VAR_SOUL_LINK_ACTIVE = 2, partner ID stored
   - Can exit to bedroom after pairing or cancel to disable Soul-Link
4. **Starter selection**: 
   - With Randomizer: Three random Pokémon appear (fixed for that playthrough)
   - Without Randomizer: Normal Bulbasaur/Squirtle/Charmander selection
5. **Receive Poké Balls**: Oak gives 5 Poké Balls after delivering parcel
   - If Nuzlocke enabled: "Your Nuzlocke Challenge has begun!" message displays
   - First encounter tracking activates from this point forward
6. **Wild encounters**: 
   - With Randomizer: Every wild Pokémon is randomly selected from 385 valid species
   - Without Randomizer: Normal encounter tables apply
7. **First encounter per route**: 
   - First wild encounter on each route: Can catch normally
   - Subsequent encounters on same route: Poké Ball is blocked with message
   - Different routes: Fresh first encounter available
8. **During battle**: Any Pokémon fainting under Nuzlocke rules is permanently marked as dead
9. **Wild Capture & Starters**: Under Nuzlocke, player is forced to provide a unique nickname
10. **On white-out**:
    - System automatically checks PC boxes for living Pokémon
    - If none exist → Full reset preserving names and challenge modes
    - If survivors exist → Player chooses to continue with boxed team or reset
    - Reset wipes everything except names, challenge mode flags, and Soul-Link partner ID
    - Starters are re-randomized and route flags cleared for the new run
11. **First rival loss**: Uses same white-out router as regular defeats

---

## Roadmap

### Phase 2: Wireless Multi-Player (In Development)

Goal: Enable real wireless connections for 2-40 players to pair in Union Room

**Planned Features:**
- Detect wireless adapter connections (mGBA link cable or physical GBA wireless)
- Hybrid Union Room: Show debug NPC when solo, real players when connected
- Real player detection and spawning as NPCs (Player 1-8)
- Pairing request/accept packet system
- Interactive player scripts for sending/receiving pair requests
- Bilateral acceptance confirmation
- Test setup with 2+ mGBA instances linked via cable emulation

**Technical Architecture:**
- Check wireless connection on Union Room entry
- If wireless detected → Use `special RunUnionRoom` for real players
- If no wireless → Use Phase 1 debug NPC fallback
- Implement link packet protocol for pairing requests (0xF0-0xF2 packet types)
- Store partner trainer ID and name on successful pairing

### Phase 3: Soul-Link Battle Mechanics (Planned)

Goal: Synchronize Pokémon deaths and enforce Soul-Link catch rules

**Planned Features:**
- Real-time packet system for Pokémon death synchronization
- Async death queue (process when partner finishes battle/menu/etc)
- Route-based soul-bonding system (paired by route index)
- Soul-Link Nuzlocke encounter rules:
  - Both players must catch their encounter or both lose it
  - Gender/species validation (encounter invalid if same gender or species as partner)
  - Encounter doesn't count for Nuzlocke if validation fails
- Minimal visual indicators (basic UI showing partner's party status, no new menus)

**Technical Architecture:**
- `struct SoulLinkPairedPokemon` storing species, gender, route, trainer IDs, alive status
- Link packets for faint events, catch validation, route pairing
- Queue system for async processing during partner's activities
- PC/party checks before healing to apply queued deaths

### Phase 4: Wipe Synchronization (Planned)

Goal: Coordinate resets between Soul-Link partners

**Planned Features:**
- Reset packet system leveraging existing `NuzlockeResetRun` infrastructure
- Partner confirmation before reset (both players must agree)
- Graceful disconnection handling (preserve pairing for reconnection)
- Preserve pairing across resets (both players reset together for fresh run)

**Technical Architecture:**
- Extend `EventScript_Nuz_ResetRun` with packet send/receive
- Add confirmation prompt: "Your partner wants to reset. Agree?"
- Handle disconnect gracefully: Store partner ID for potential reconnection
- Reset synchronization: Both players warp to bedroom simultaneously

### Phase 5: Advanced Features (Optional)

**Possible Future Additions:**
- Random partner wheel spinner (animated selection from connected players)
- Partner reconnection after disconnect (resume pairing via Union Room)
- Spectator mode (watch partner's game in real-time)
- Achievement system for completed Soul-Link runs
- Global matchmaking (server-based pairing for cross-region Soul-Link)

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

### Variable System
- `VAR_NUZLOCKE_ACTIVE (0x4090)`: Nuzlocke mode enabled (0 = off, 1 = on)
- `VAR_SOUL_LINK_ACTIVE (0x4091)`: Soul-Link state (0 = off, 1 = searching, 2 = paired)
- `VAR_SOUL_LINK_PARTNER_ID (0x4092)`: Stores partner's trainer ID when paired

### Flag System
- `FLAG_WILD_RANDOMIZER_ENABLED`: Master switch for randomizer
- `FLAG_NUZLOCKE_ENCOUNTERS_ACTIVE (0x200)`: Set when Oak gives Poké Balls
- `FLAG_NUZLOCKE_TEMP_BLOCK_CATCH (0x4FE)`: Temporary battle flag signaling "catch blocked"
- `FLAG_NUZLOCKE_ROUTE_BASE (0x900-0x9FF)`: 256 dynamic route flags, auto-assigned by map section ID
- `FLAG_HIDE_UNION_ROOM_PLAYER_1-8`: Control NPC visibility in Union Room

### Union Room Architecture
- **Map**: `MAP_UNION_ROOM` with 9 object events (receptionist + 8 player slots)
- **Elevation**: All objects, warps, and triggers use elevation 0 for proper collision
- **Coord triggers**: 15 triggers total (3×3 for exit prompts, 3×3 for flag resets, 9 for warps)
- **Warp system**: Three-tile-wide door using coord triggers (not map warp events) for reliable behavior
- **Soul-Link modes**:
  - Searching (1): Shows debug NPC, prompts on exit, welcome message
  - Paired (2): Debug NPC shows "Already paired", instant warp on exit
  - Off (0): Normal wireless Union Room behavior (not used in Phase 1)