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
    
    if (starChaser != nullptr) {
        starChaser->Draw();
    }
    // Debug: Display the spaceship's position on the screen
    /*char positionText[128];
    sprintf_s(positionText, "Spaceship at: %d, %d",
        static_cast<int>(spaceship->position.x),
        static_cast<int>(spaceship->position.y));
    DrawText(positionText, 10, 10, 20, RED); */
}

void Grid::ToggleCell(int x, int y) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        cells[x][y].blocked = !cells[x][y].blocked;
    }
}

void Grid::PlaceEntities() {
    std::vector<Vector2> occupiedPositions;

    auto isPositionOccupied = [&occupiedPositions](const Vector2& position) -> bool {
        for (const auto& occupiedPosition : occupiedPositions) {
            if (occupiedPosition.x == position.x && occupiedPosition.y == position.y) {
                return true;
            }
        }
        return false;
        };

    auto isPositionBlocked = [this](const Vector2& position) -> bool {
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);
        return cells[x][y].blocked;
        };

    // Lambda function to place an entity on the grid
    auto placeEntity = [this, &occupiedPositions, &isPositionOccupied, &isPositionBlocked](auto** entity, auto constructor) {
        bool placed = false;
        while (!placed) {
            int x = GetRandomValue(0, gridSize - 1);
            int y = GetRandomValue(0, gridSize - 1);
            Vector2 position = { static_cast<float>(x), static_cast<float>(y) };
            if (!isPositionBlocked(position) && !isPositionOccupied(position)) {
                *entity = constructor(position); // Use the constructor passed as a parameter
                occupiedPositions.push_back(position);
                placed = true;
            }
        }
        };

    // Place Spaceship
    placeEntity(&spaceship, [this](Vector2 pos) { return new Spaceship(pos); });

    // Place Trading Post
    placeEntity(&tradingPost, [this](Vector2 pos) { return new TradingPost(pos); });

    // Place Fallen Star
    placeEntity(&fallenStar, [this](Vector2 pos) { return new FallenStar(pos); });

    // Place StarChaser
    placeEntity(&starChaser, [this](Vector2 pos) { return new StarChaser(pos, 100.0f, fallenStar->position, tradingPost->position, spaceship->position); });
}



Vector2 Grid::GetFallenStarPosition() {
    /*if (fallenStar != nullptr) {
        return fallenStar->position;
    }
    else {
        // Handle the error or return a default position
        std::cerr << "Error: Attempted to access position of a nonexistent FallenStar." << std::endl;*/
        return { -1.0f, -1.0f }; // Example default position indicating an error
    //}
}

Vector2 Grid::GetTradingPostPosition() {
    return tradingPost->position;
}

Vector2 Grid::GetSpaceshipPosition() {
    return spaceship->position;
}

Grid::~Grid() {
    delete spaceship; // Free the memory allocated for the spaceship
    spaceship = nullptr; // Set the pointer to nullptr to avoid dangling pointer
    delete tradingPost;
    tradingPost = nullptr;
    delete fallenStar;
    fallenStar = nullptr;
    delete starChaser;
    starChaser = nullptr;
}