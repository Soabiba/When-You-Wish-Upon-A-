#include "raylib.h"
#include "Level.h"

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Star Chaser Simulation");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Your drawing code here

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}