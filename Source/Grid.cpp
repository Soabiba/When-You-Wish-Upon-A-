#include "Level.h"

Grid::Grid() {
    Initialize();
}

void Grid::Initialize() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            cells[i][j].blocked = GetRandomValue(0, 1); // Randomly block cells
        }
    }
}

void Grid::Update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int gridX = static_cast<int>(mousePos.x / Grid::cellSize);
            int gridY = static_cast<int>(mousePos.y / Grid::cellSize);
            ToggleCell(gridX, gridY); // Toggle cell state on click
        }
}

void Grid::Draw() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            Color color = cells[i][j].blocked ? DARKGRAY : LIGHTGRAY;
            DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, color);
            DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, BLACK); // Cell border
        }
    }
}

void Grid::ToggleCell(int x, int y) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        cells[x][y].blocked = !cells[x][y].blocked;
    }
}