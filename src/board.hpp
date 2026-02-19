#pragma once

/**
 * @file board.hpp
 * @brief Board rendering library for classic board games.
 *
 * Provides Raylib-based rendering for Nine Men's Morris and Go boards,
 * including drawing primitives for pieces, highlights, and territory markers.
 */

#include <string>

/// @name Player Constants
/// @{
constexpr int kEmpty = 0;     ///< Empty cell
constexpr int kPlayer1 = 1;   ///< Black player
constexpr int kPlayer2 = 2;   ///< White player
/// @}

/**
 * @brief Open a Morris board window.
 *
 * Creates a window with 24 positions arranged in three concentric squares
 * with cross connections. The board uses a fixed layout optimized for
 * Nine Men's Morris gameplay.
 */
void InitMorrisBoard();

/**
 * @brief Open a Go board window with a square grid.
 * @param size Grid size (common values: 9, 13, 19).
 *
 * Creates a window with a size x size grid. Star points are automatically
 * placed according to standard Go conventions for the given board size.
 */
void InitGoBoard(int size);

/**
 * @brief Close the board window.
 *
 * Closes the Raylib window. Call once when the game ends or when
 * transitioning back to the menu.
 */
void CloseBoard();

/**
 * @brief Check if the user requested window close.
 * @return true if the user clicked the window close button.
 */
bool ShouldClose();

/**
 * @brief Begin a new frame.
 *
 * Clears the screen and draws the board background and grid lines.
 * Call once per frame before any drawing operations.
 */
void BeginFrame();

/**
 * @brief End the current frame and display it.
 *
 * Flushes all drawing operations to the screen.
 * Call once per frame after all drawing is complete.
 */
void EndFrame();

/**
 * @brief Draw a game piece at a board position.
 * @param position Board position index (0-23 for Morris, 0 to size*size-1 for Go).
 * @param player Player constant (kPlayer1 for black, kPlayer2 for white).
 */
void DrawPiece(int position, int player);

/**
 * @brief Draw a highlight ring around a board position.
 * @param position Board position index to highlight.
 *
 * Draws a yellow ring around the position, useful for showing
 * selected pieces or valid move targets.
 */
void DrawHighlight(int position);

/**
 * @brief Draw a territory marker at an empty position.
 * @param position Board position index.
 * @param player Player who owns the territory (kPlayer1 or kPlayer2).
 *
 * Draws a small square marker indicating territory ownership,
 * typically used in Go for scoring display.
 */
void DrawTerritory(int position, int player);

/**
 * @brief Draw status text at the bottom of the window.
 * @param text Status message to display.
 *
 * Text is automatically word-wrapped to fit the window width.
 */
void DrawStatus(const std::string& text);

/**
 * @brief Get the board position clicked by the user.
 * @return Position index if a valid position was clicked, -1 otherwise.
 *
 * For Morris boards, returns 0-23. For Go boards, returns 0 to size*size-1.
 * Only detects clicks that occur within the click threshold of a position.
 */
int GetClickedPosition();

/**
 * @brief Check if the user pressed the pass key.
 * @return true if the P key was pressed this frame.
 *
 * Used in Go to allow players to pass their turn.
 */
bool IsPassPressed();
