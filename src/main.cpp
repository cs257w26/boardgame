#include "board.hpp"
#include "menu.hpp"

#include "raylib.h"

/**
 * @brief Application states.
 */
enum class GameState {
    Menu,     ///< Main menu - select game type
    Playing   ///< Active game
};

/**
 * @brief Initialize the appropriate board based on menu selection.
 * @param option The selected menu option.
 */
static void InitBoardForOption(MenuOption option) {
    switch (option) {
        case MenuOption::Morris:
            InitMorrisBoard();
            break;
        case MenuOption::Go9:
            InitGoBoard(9);
            break;
        case MenuOption::Go13:
            InitGoBoard(13);
            break;
        case MenuOption::Go19:
            InitGoBoard(19);
            break;
        default:
            break;
    }
}

/**
 * @brief Get the status text for the current game type.
 * @param option The current game type.
 * @return Status string describing the game.
 */
static const char* GetGameStatus(MenuOption option) {
    switch (option) {
        case MenuOption::Morris:
            return "Nine Men's Morris - ESC to pause";
        case MenuOption::Go9:
            return "Go (9x9) - ESC to pause";
        case MenuOption::Go13:
            return "Go (13x13) - ESC to pause";
        case MenuOption::Go19:
            return "Go (19x19) - ESC to pause";
        default:
            return "ESC to pause";
    }
}

/**
 * @brief Draw pause menu overlay and handle input.
 * @return 0 to resume, 1 to return to menu, -1 to quit application.
 */
static int RunPauseMenu() {
    int selected = 0;
    const char* options[] = {"Resume", "Return to Menu"};
    constexpr int numOptions = 2;
    constexpr int fontSize = 24;
    constexpr int itemHeight = 40;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            selected--;
            if (selected < 0) selected = numOptions - 1;
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            selected++;
            if (selected >= numOptions) selected = 0;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            return selected;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            return 0;  // ESC again resumes
        }

        // Draw
        BeginFrame();
        DrawStatus("");

        // Semi-transparent overlay
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 150});

        // Pause title
        const char* title = "PAUSED";
        int titleWidth = MeasureText(title, 40);
        int centerX = GetScreenWidth() / 2;
        int startY = GetScreenHeight() / 2 - 60;
        DrawText(title, centerX - titleWidth / 2, startY, 40, WHITE);

        // Menu options
        for (int i = 0; i < numOptions; i++) {
            int y = startY + 70 + i * itemHeight;
            int textWidth = MeasureText(options[i], fontSize);
            int x = centerX - textWidth / 2;

            if (i == selected) {
                DrawText(">", x - 25, y, fontSize, YELLOW);
                DrawText(options[i], x, y, fontSize, YELLOW);
            } else {
                DrawText(options[i], x, y, fontSize, LIGHTGRAY);
            }
        }

        EndFrame();
    }

    return -1;  // Window closed
}

int main() {
    GameState state = GameState::Menu;
    int menuSelection = 0;
    MenuOption currentGame = MenuOption::Morris;
    bool running = true;

    while (running) {
        if (state == GameState::Menu) {
            InitMenu();

            bool menuOpen = true;
            while (menuOpen) {
                if (ShouldCloseMenu()) {
                    CloseMenu();
                    running = false;
                    menuOpen = false;
                    break;
                }

                menuSelection = GetMenuInput(menuSelection);
                DrawMenu(menuSelection);

                if (IsMenuConfirmed()) {
                    auto selected = static_cast<MenuOption>(menuSelection);

                    if (selected == MenuOption::Quit) {
                        CloseMenu();
                        running = false;
                        menuOpen = false;
                    } else {
                        currentGame = selected;
                        CloseMenu();
                        state = GameState::Playing;
                        menuOpen = false;
                    }
                }
            }
        }

        if (running && state == GameState::Playing) {
            InitBoardForOption(currentGame);

            bool gameOpen = true;
            while (gameOpen) {
                if (ShouldClose()) {
                    CloseBoard();
                    running = false;
                    gameOpen = false;
                    break;
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    int result = RunPauseMenu();
                    if (result == 1) {
                        // Return to menu
                        CloseBoard();
                        state = GameState::Menu;
                        gameOpen = false;
                    } else if (result == -1) {
                        // Window closed
                        CloseBoard();
                        running = false;
                        gameOpen = false;
                    }
                    // result == 0: resume, continue loop
                } else {
                    BeginFrame();
                    DrawStatus(GetGameStatus(currentGame));
                    EndFrame();
                }
            }
        }
    }

    return 0;
}
