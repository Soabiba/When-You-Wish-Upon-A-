#include "raylib.h"
#include "Level.h"

int main() {
    InitWindow(Grid::gridSize * Grid::cellSize, Grid::gridSize * Grid::cellSize, "Grid World");
    SetTargetFPS(60);

    Grid grid; // Create an instance of Grid

    while (!WindowShouldClose()) {
        
        grid.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.Draw(); // Draw the grid

        EndDrawing();
    }

    CloseWindow();

    return 0;
}