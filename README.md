# Number Game (Sliding Puzzle)

A simple C++17 console implementation of the classic 4x4 sliding puzzle game (also known as the 15-puzzle).

## Features
- 4x4 board with one empty space
- Randomized, solvable starting board
- Move tiles using WASD keys
- Detects win condition
- Colored output for correct tiles (Linux/Unix terminals)

## Controls
- `w` — Move empty space up
- `a` — Move empty space left
- `s` — Move empty space down
- `d` — Move empty space right
- `q` — Quit the game

## How to Build

1. Make sure you have a C++17 compatible compiler (e.g., g++ 7+).
2. Build with:
   ```sh
   g++ -std=c++17 -g main.cpp BoardImp.cpp TileImp.cpp -o numgame
   ```
3. Run with:
   ```sh
   ./numgame
   ```

## File Structure
- `main.cpp` — Entry point
- `Board.h` / `BoardImp.cpp` — Board logic and game loop
- `Tile.h` / `TileImp.cpp` — Tile representation

## Notes
- Works best in terminals that support ANSI color codes.
- Only basic error handling is implemented.

## License
No license
