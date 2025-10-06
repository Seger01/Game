# Tower Defense Game Design Document

## Overview
A complete tower defense game built on the EngineBravo engine, featuring multiple tower types, enemy waves, resource management, and strategic gameplay.

## Core Mechanics

### Enemy System
- **Wave-based spawning**: Enemies spawn in waves with increasing difficulty
- **Pathfinding**: Enemies follow a predefined waypoint path
- **Health scaling**: Enemy health increases with each wave (50 + wave * 20)
- **Speed scaling**: Enemy speed increases with each wave (50 + wave * 5)
- **Rewards**: Players earn money for each defeated enemy (10 + wave * 2)
- **Base damage**: Enemies that reach the end deal 10 damage to the base

### Tower System
Four distinct tower types, each with unique strengths:

1. **Basic Tower**
   - Cost: $100
   - Range: 100 units
   - Damage: 10
   - Fire Rate: 1.0s
   - Best for: General purpose, early game

2. **Rapid Tower**
   - Cost: $150
   - Range: 80 units
   - Damage: 5
   - Fire Rate: 0.3s
   - Best for: High DPS on single targets, groups

3. **Sniper Tower**
   - Cost: $250
   - Range: 200 units
   - Damage: 50
   - Fire Rate: 3.0s
   - Best for: Long-range elimination, tough enemies

4. **Splash Tower**
   - Cost: $200
   - Range: 90 units
   - Damage: 15
   - Fire Rate: 1.5s
   - Best for: Area damage, clustered enemies

### Resource Management
- Starting money: $500
- Earn money by defeating enemies
- Bonus money for completing waves (50 + wave * 10)
- Must balance spending on towers vs saving for later waves

### Win/Lose Conditions
- **Victory**: Complete all 10 waves with base health > 0
- **Defeat**: Base health reaches 0

## Game Balance

### Wave Progression
- Wave 1-3: Easy (5-11 enemies)
- Wave 4-6: Medium (14-20 enemies)
- Wave 7-9: Hard (23-29 enemies)
- Wave 10: Boss wave (32 enemies)

### Economy Balance
Total money earned per wave (assuming all enemies defeated):
- Wave 1: $75 (spawn) + $50 (bonus) = $125
- Wave 5: $175 (spawn) + $100 (bonus) = $275
- Wave 10: $320 (spawn) + $150 (bonus) = $470

This allows for approximately:
- 5 basic towers by wave 5
- 2-3 advanced towers by wave 10
- Strategic choices required throughout

### Strategic Depth
- Tower placement matters (early path = more damage)
- Tower synergy (mix types for effectiveness)
- Resource timing (when to save vs spend)
- Adaptation to wave difficulty

## Technical Implementation

### Architecture
- **Component-based**: Each game object (enemy, tower, projectile) uses components
- **Event-driven**: Game state changes trigger appropriate responses
- **Modular**: Easy to add new tower types or enemy variants

### Key Classes
- `TDGameManager`: Controls game state, waves, and resources
- `TDEnemy`: Enemy behavior and pathfinding
- `TDTower`: Tower targeting and shooting logic
- `TDProjectile`: Projectile movement and collision
- `TDPlayerController`: Input handling and tower placement

### Visual Design
- Enemies: Dinosaur sprites
- Towers: Color-coded bullet sprites
- Projectiles: Small bullet sprites
- Path: Silver coin markers
- Clear visual distinction between types

## Future Enhancements

### Potential Features
1. Tower upgrades (increase damage, range, fire rate)
2. More enemy types (fast, tank, flying)
3. Special abilities (slow, freeze, area damage)
4. Multiple difficulty levels
5. Level selection with different paths
6. Score tracking and leaderboards
7. Sound effects and music
8. Visual effects (explosions, hit indicators)
9. UI overlays (health bars, money counter)
10. Save/load game state

### Balance Improvements
- Fine-tune enemy health/speed curves
- Adjust tower costs and stats
- Add difficulty modifiers
- Implement tower placement restrictions (limited spots)

## Conclusion
This tower defense game provides an engaging, strategic experience with room for expansion and refinement. The core mechanics are solid and the balance encourages thoughtful gameplay.