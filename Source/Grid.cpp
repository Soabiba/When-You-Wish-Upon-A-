#include "Level.h"


Grid::Grid() {
    Initialize();
    PlaceEntities();
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

    if (spaceship != nullptr) { // Check if the spaceship has been created
        spaceship->Draw(); // Call the Draw method of the Spaceship
    }

    if (tradingPost != nullptr) {
        tradingPost->Draw();
    }

    if (fallenStar != nullptr) {
        fallenStar->Draw();
    }

    // Debug: Display the spaceship's position on the screen
    /*char positionText[128];
    sprintf_s(positionText, "Spaceship at: %d, %d",
        static_cast<int>(spaceship->position.x),
        static_cast<int>(spaceship->position.y));
    DrawText(positionText, 10, 10, 20, RED); // Adjust position and size as needed*/
}

void Grid::ToggleCell(int x, int y) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        cells[x][y].blocked = !cells[x][y].blocked;
    }
}

void Grid::PlaceEntities() {
    bool placed = false;
    while (!placed) {
        int x = GetRandomValue(0, gridSize - 1);
        int y = GetRandomValue(0, gridSize - 1);
        if (!cells[x][y].blocked) {
            // Store grid coordinates directly
            Vector2 gridPosition = { static_cast<float>(x), static_cast<float>(y) };
            spaceship = new Spaceship(gridPosition); // Use grid coords
            placed = true;
        }
    }

    // Place Trading Post
    bool placedTP = false;
    while (!placedTP) {
        int x = GetRandomValue(0, gridSize - 1);
        int y = GetRandomValue(0, gridSize - 1);
        if (!cells[x][y].blocked) {
            Vector2 position = { static_cast<float>(x), static_cast<float>(y) };
            tradingPost = new TradingPost(position);
            placedTP = true;
        }
    }

    // Place Fallen Star
    bool placedFS = false;
    while (!placedFS) {
        int x = GetRandomValue(0, gridSize - 1);
        int y = GetRandomValue(0, gridSize - 1);
        if (!cells[x][y].blocked && !(tradingPost->position.x == x && tradingPost->position.y == y)) {
            Vector2 position = { static_cast<float>(x), static_cast<float>(y) };
            fallenStar = new FallenStar(position);
            placedFS = true;
        }
    }
}

Grid::~Grid() {
    delete spaceship; // Free the memory allocated for the spaceship
    spaceship = nullptr; // Set the pointer to nullptr to avoid dangling pointer
    delete tradingPost;
    tradingPost = nullptr;
    delete fallenStar;
    fallenStar = nullptr;
}