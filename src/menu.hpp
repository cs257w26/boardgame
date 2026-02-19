#pragma once

/**
 * @file menu.hpp
 * @brief Video game style menu system for the board game application.
 *
 * Provides a classic SNES/PS1 era menu with centered text, highlight bar,
 * and keyboard/mouse navigation.
 */

/**
 * @brief Available menu options.
 */
enum class MenuOption {
    Morris,   ///< Nine Men's Morris
    Go9,      ///< Go on 9x9 board
    Go13,     ///< Go on 13x13 board
    Go19,     ///< Go on 19x19 board
    Quit,     ///< Exit the application
    Count     ///< Number of menu options (for iteration)
};

/**
 * @brief Initialize the menu window.
 *
 * Creates a Raylib window sized for the menu display.
 * Must be called before any other menu functions.
 */
void InitMenu();

/**
 * @brief Close the menu window.
 *
 * Closes the Raylib window. Call when transitioning to a game
 * or exiting the application.
 */
void CloseMenu();

/**
 * @brief Draw the menu with the current selection highlighted.
 * @param selected Index of the currently selected menu option (0 to Count-1).
 */
void DrawMenu(int selected);

/**
 * @brief Process input and return the new selection index.
 * @param current Current selection index.
 * @return New selection index after processing arrow key or mouse input.
 */
int GetMenuInput(int current);

/**
 * @brief Check if the user confirmed their selection.
 * @return true if Enter was pressed or mouse clicked on selection.
 */
bool IsMenuConfirmed();

/**
 * @brief Check if the menu window should close.
 * @return true if the user closed the window.
 */
bool ShouldCloseMenu();
