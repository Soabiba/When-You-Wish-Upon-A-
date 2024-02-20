#include "Level.h"

int main() {
    InitWindow(Grid::gridSize * Grid::cellSize, Grid::gridSize * Grid::cellSize, "Grid World");
    SetTargetFPS(60);

    Grid grid; // Create an instance of Grid

    while (!WindowShouldClose()) {
        
        grid.Update();
        /*if (grid.spaceship != nullptr && grid.tradingPost != nullptr && grid.fallenStar != nullptr && grid.starChaser != nullptr) {
            grid.starChaser->Update(); // Or any other method that updates game entities
        }*/

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.Draw(); // Draw the grid

        EndDrawing();
    }

    CloseWindow();

    return 0;
}