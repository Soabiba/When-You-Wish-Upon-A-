#include "Level.h"

int main() {
    InitWindow(Grid::gridSize * Grid::cellSize, Grid::gridSize * Grid::cellSize, "Grid World");
    SetTargetFPS(60);

    Grid grid; // Create an instance of Grid
    Vector2 starchaserPos = { static_cast<float>(GetRandomValue(0, gridSize - 1)),
                              static_cast<float>(GetRandomValue(0, gridSize - 1)) };
    Starchaser starchaser(starchaserPos);

    while (!WindowShouldClose()) {
        
        grid.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.Draw(); // Draw the grid
        starchaser.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}