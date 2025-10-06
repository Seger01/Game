# Game
This repo is the game that I want to make alongside the engine

## Tower Defense Game

A fun and engaging tower defense game built on the EngineBravo game engine!

### Gameplay

Defend your base from 10 waves of increasingly difficult enemies. Place towers strategically along the path to destroy enemies before they reach the end.

### How to Play

1. **Starting Resources**: You begin with $500 and 100 base health
2. **Place Towers**: Select a tower type (1-4 keys) and click to place
3. **Defend**: Towers automatically shoot at nearby enemies
4. **Survive**: Complete all 10 waves without losing all your base health

### Tower Types

- **Basic Tower (1)** - $100
  - Balanced tower with moderate range, damage, and fire rate
  - Good all-around choice for beginners
  
- **Rapid Tower (2)** - $150
  - Shoots quickly with shorter range
  - Perfect for dealing with groups of weak enemies
  
- **Sniper Tower (3)** - $250
  - Long range with high damage but slow fire rate
  - Excellent for picking off strong enemies from afar
  
- **Splash Tower (4)** - $200
  - Medium range with area damage
  - Great for handling clustered enemies

### Strategy Tips

- Place towers early in the path to maximize damage time
- Mix tower types for balanced defense
- Save money for stronger towers in later waves
- Watch the enemy path and plan tower placement accordingly

### Controls

- **1, 2, 3, 4**: Select tower type
- **Left Click**: Place selected tower
- **ESC**: Quit game

### Building and Running

```bash
cd code
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
./bin/Game
```

### Requirements

- CMake 3.10+
- C++23 compiler
- OpenGL
- ALSA (Linux audio)
- X11 development libraries

Enjoy defending your base!
