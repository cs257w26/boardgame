# Board Game Library

Rendering and input library for CS 257 HW 5 (Nine Men's Morris / Go).

## Getting Started

Clone this repo, then build:

```bash
cmake -S . -B build
cmake --build build
./build/boardgame
```

The first build takes a minute or two as CMake downloads and compiles Raylib. Subsequent builds are fast.

On Windows, run from a **Developer Command Prompt** and use `build\boardgame.exe` instead.

## Files

- `src/board.hpp` — Board library header (do not modify)
- `src/board.cpp` — Board library implementation (do not modify)
- `src/main.cpp` — Starter main file (replace with your game logic)
- `CMakeLists.txt` — Build configuration

**Do not modify `board.hpp` or `board.cpp`** — the instructor may push updates to these files during the assignment.

Add your own `.cpp` files in `src/` and they will be compiled automatically.
