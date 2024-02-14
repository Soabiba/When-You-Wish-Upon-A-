#include "Level.h"

void Spaceship::Draw() {
    // Convert grid coordinates to pixel coordinates for drawing
    int pixelX = static_cast<int>(position.x) * Grid::cellSize + Grid::cellSize / 2;
    int pixelY = static_cast<int>(position.y) * Grid::cellSize + Grid::cellSize / 2;

    DrawCircle(pixelX, pixelY, Grid::cellSize / 4, BLUE);
}

void TradingPost::Draw() {
    int pixelX = static_cast<int>(position.x) * Grid::cellSize + Grid::cellSize / 2;
    int pixelY = static_cast<int>(position.y) * Grid::cellSize + Grid::cellSize / 2;
    DrawRectangle(pixelX - Grid::cellSize / 2, pixelY - Grid::cellSize / 2, Grid::cellSize, Grid::cellSize, GREEN);
}

void FallenStar::Draw() {
    int pixelX = static_cast<int>(position.x) * Grid::cellSize + Grid::cellSize / 2;
    int pixelY = static_cast<int>(position.y) * Grid::cellSize + Grid::cellSize / 2;
    DrawCircle(pixelX, pixelY, Grid::cellSize / 4, YELLOW);
}