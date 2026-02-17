#include "board.hpp"

int main() {
  InitMorrisBoard();  // For Go: InitGoBoard(9)

  while (!ShouldClose()) {
    BeginFrame();
    DrawStatus("Board is working!");
    EndFrame();
  }

  CloseBoard();
  return 0;
}
