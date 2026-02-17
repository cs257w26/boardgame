#pragma once

#include <string>

// Player and cell constants.
constexpr int kEmpty = 0;
constexpr int kPlayer1 = 1;   // Black
constexpr int kPlayer2 = 2;   // White

// Open a Morris board window with 24 positions arranged in three
// concentric squares with cross connections.
void InitMorrisBoard();

// Open a Go board window with a square grid of the given size.
// Common sizes are 9, 13, and 19.
void InitGoBoard(int size);

// Close the board window. Call once when the game ends.
void CloseBoard();

// Returns true when the user closes the window.
bool ShouldClose();

// Begin a new frame. Clears the screen and draws the board.
// Call once per frame before any drawing.
void BeginFrame();

// End the current frame and display it.
// Call once per frame after all drawing.
void EndFrame();

// Draw a game piece at the given board position.
// player should be kPlayer1 (black) or kPlayer2 (white).
void DrawPiece(int position, int player);

// Draw a highlight ring around a board position.
void DrawHighlight(int position);

// Draw a small territory marker at an empty position.
void DrawTerritory(int position, int player);

// Draw status text at the bottom of the window.
void DrawStatus(const std::string& text);

// If the user clicked a board position this frame, returns its index.
// Returns -1 if no position was clicked.
// For the fixed layout, returns 0-23.
// For grid boards, returns 0 to size*size - 1.
int GetClickedPosition();

// Returns true if the user pressed the P key this frame.
bool IsPassPressed();
