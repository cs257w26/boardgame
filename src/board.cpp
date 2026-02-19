#include "board.hpp"

#include "raylib.h"

#include <utility>
#include <vector>

// Board layout types.
enum BoardType { kNone, kFixedLayout, kGrid };

// Internal state.
static BoardType board_type = kNone;
static int board_size = 0;
static std::vector<Vector2> positions;
static std::vector<std::pair<int, int>> line_segments;
static std::vector<int> star_points;
static float piece_radius;
static float click_threshold;
static int status_y;

// Background colors.
static const Color kGridBg = {210, 180, 120, 255};
static const Color kFixedBg = {210, 195, 170, 255};
static const Color kDotColor = {180, 165, 140, 255};

// Screen positions for the 24-position fixed layout.
static const Vector2 kFixedPositions[24] = {
    {100, 100}, {350, 100}, {600, 100}, {183, 183}, {350, 183}, {517, 183},
    {267, 267}, {350, 267}, {433, 267}, {100, 350}, {183, 350}, {267, 350},
    {433, 350}, {517, 350}, {600, 350}, {267, 433}, {350, 433}, {433, 433},
    {183, 517}, {350, 517}, {517, 517}, {100, 600}, {350, 600}, {600, 600},
};

// Line connections for the fixed layout.
static const int kFixedLines[][2] = {
    {0, 1}, {1, 2}, {2, 14},  {14, 23}, {23, 22}, {22, 21}, {21, 9},  {9, 0},
    {3, 4}, {4, 5}, {5, 13},  {13, 20}, {20, 19}, {19, 18}, {18, 10}, {10, 3},
    {6, 7}, {7, 8}, {8, 12},  {12, 17}, {17, 16}, {16, 15}, {15, 11}, {11, 6},
    {1, 4}, {4, 7}, {12, 13}, {13, 14}, {16, 19}, {19, 22}, {9, 10},  {10, 11},
};
constexpr int kNumFixedLines = 32;

// Returns true if (row, col) is a star point on a grid of the given size.
static bool IsStarPoint(int row, int col, int size) {
  if (size == 9) {
    return ((row == 2 || row == 6) && (col == 2 || col == 6)) ||
           (row == 4 && col == 4);
  } else if (size == 13) {
    return (row == 3 || row == 6 || row == 9) &&
           (col == 3 || col == 6 || col == 9);
  } else if (size == 19) {
    return (row == 3 || row == 9 || row == 15) &&
           (col == 3 || col == 9 || col == 15);
  }
  return false;
}

void InitMorrisBoard() {
  board_type = kFixedLayout;
  positions.clear();
  line_segments.clear();

  for (int i = 0; i < 24; i++) {
    positions.push_back(kFixedPositions[i]);
  }
  for (int i = 0; i < kNumFixedLines; i++) {
    line_segments.push_back({kFixedLines[i][0], kFixedLines[i][1]});
  }

  piece_radius = 20;
  click_threshold = 25;
  status_y = 660;

  InitWindow(700, 750, "Board Game");
  SetTargetFPS(60);
  SetExitKey(0);
}

void InitGoBoard(int size) {
  board_type = kGrid;
  board_size = size;
  positions.clear();
  line_segments.clear();
  star_points.clear();

  int cell_size;
  if (size <= 9) {
    cell_size = 60;
  } else if (size <= 13) {
    cell_size = 45;
  } else {
    cell_size = 34;
  }

  int margin = cell_size + 10;
  int grid_pixels = (board_size - 1) * cell_size;

  for (int row = 0; row < board_size; row++) {
    for (int col = 0; col < board_size; col++) {
      float x = margin + col * cell_size;
      float y = margin + row * cell_size;
      positions.push_back({x, y});

      if (IsStarPoint(row, col, board_size)) {
        star_points.push_back(row * board_size + col);
      }
    }
  }

  for (int row = 0; row < board_size; row++) {
    for (int col = 0; col < board_size; col++) {
      int pos = row * board_size + col;
      if (col < board_size - 1) {
        line_segments.push_back({pos, pos + 1});
      }
      if (row < board_size - 1) {
        line_segments.push_back({pos, pos + board_size});
      }
    }
  }

  piece_radius = cell_size * 0.43f;
  click_threshold = cell_size * 0.45f;

  int window_width = grid_pixels + margin * 2;
  int window_height = window_width + 50;
  status_y = window_width + 15;

  InitWindow(window_width, window_height, "Board Game");
  SetTargetFPS(60);
  SetExitKey(0);
}

void CloseBoard() {
  CloseWindow();
}

bool ShouldClose() {
  return WindowShouldClose();
}

void BeginFrame() {
  BeginDrawing();

  if (board_type == kGrid) {
    ClearBackground(kGridBg);
  } else {
    ClearBackground(kFixedBg);
  }

  float thickness = (board_type == kGrid) ? 1.5f : 3.0f;
  Color line_color = (board_type == kGrid) ? BLACK : DARKGRAY;
  for (auto& [a, b] : line_segments) {
    DrawLineEx(positions[a], positions[b], thickness, line_color);
  }

  if (board_type == kGrid) {
    for (int idx : star_points) {
      DrawCircle(positions[idx].x, positions[idx].y, 4, BLACK);
    }
  } else {
    for (auto& p : positions) {
      DrawCircle(p.x, p.y, 6, kDotColor);
    }
  }
}

void EndFrame() {
  EndDrawing();
}

void DrawPiece(int position, int player) {
  Vector2 p = positions[position];
  if (player == kPlayer1) {
    DrawCircle(p.x, p.y, piece_radius, BLACK);
  } else {
    DrawCircle(p.x, p.y, piece_radius, WHITE);
    DrawCircleLines(p.x, p.y, piece_radius, DARKGRAY);
  }
}

void DrawHighlight(int position) {
  Vector2 p = positions[position];
  DrawCircleLines(p.x, p.y, piece_radius + 3, YELLOW);
  DrawCircleLines(p.x, p.y, piece_radius + 4, YELLOW);
}

void DrawTerritory(int position, int player) {
  Vector2 p = positions[position];
  float size = piece_radius * 0.35f;
  Color c = (player == kPlayer1) ? BLACK : WHITE;
  DrawRectangle(p.x - size, p.y - size, size * 2, size * 2, c);
  if (player == kPlayer2) {
    DrawRectangleLines(p.x - size, p.y - size, size * 2, size * 2, DARKGRAY);
  }
}

void DrawStatus(const std::string& text) {
  int x = (board_type == kGrid) ? 80 : 100;
  DrawText(text.c_str(), x, status_y, 20, DARKGRAY);
}

int GetClickedPosition() {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    return -1;
  }
  Vector2 mouse = GetMousePosition();
  for (int i = 0; i < static_cast<int>(positions.size()); i++) {
    float dx = mouse.x - positions[i].x;
    float dy = mouse.y - positions[i].y;
    if (dx * dx + dy * dy < click_threshold * click_threshold) {
      return i;
    }
  }
  return -1;
}

bool IsPassPressed() {
  return IsKeyPressed(KEY_P);
}
