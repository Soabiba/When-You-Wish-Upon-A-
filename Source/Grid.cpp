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
    if (starChaser != nullptr && starChaser->needsPathUpdate) {
        Vector2 target = starChaser ? starChaser->position : Vector2{ 0, 0 };
        // Determine the target based on the StarChaser's current state
        switch (starChaser->state) {
        case SearchingForStar:
            target = GetFallenStarPosition();
            break;
        case CarryingStar:
            target = GetTradingPostPosition();
            break;
        case Resting:
            target = GetSpaceshipPosition();
            break;
        }
        starChaser->currentPath = AStarSearch(*this, starChaser->position, target); // Recalculate path
        starChaser->needsPathUpdate = false;
    }

    // Ensure the StarChaser updates based on the recalculated path or its current behavior
    if (starChaser != nullptr && currentMode == PathFindMode) {
        starChaser->Update(*this);
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
        starChaser->DrawStamina();
    }
    // Debug: Display the spaceship's position on the screen
    /*char positionText[128];
    sprintf_s(positionText, "Spaceship at: %d, %d",
        static_cast<int>(starChaser->position.x),
        static_cast<int>(starChaser->position.y));
    DrawText(positionText, 10, 10, 20, RED); */
}

bool Grid::IsCellOccupied(Vector2 position) const {
    if (spaceship && Vector2Equals(spaceship->position, position, 0.001f)) return true;
    if (tradingPost && Vector2Equals(tradingPost->position, position, 0.001f)) return true;
    if (fallenStar && Vector2Equals(fallenStar->position, position, 0.001f)) return true;
    if (starChaser && Vector2Equals(starChaser->position, position, 0.001f)) return true;
    return false;
}

void Grid::ToggleCell(int x, int y) {
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) return;
    Vector2 position = { static_cast<float>(x), static_cast<float>(y) };

    // Prevent toggling a cell to blocked if it's occupied
    if (currentMode == ToggleMode && !IsCellOccupied(position)) {
        cells[x][y].blocked = !cells[x][y].blocked;
    }
}

void Grid::TriggerPathFind(int x, int y) {
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) return;

    if (currentMode == PathFindMode && starChaser != nullptr) {
        Vector2 target = { static_cast<float>(x), static_cast<float>(y) };
        starChaser->currentPath = AStarSearch(*this, starChaser->position, target);
        starChaser->needsPathUpdate = false; // Path is now updated
    }
}

bool Grid::IsCellBlocked(Vector2 position) const {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        return cells[x][y].blocked;
    }
    return true;  // Treat out-of-bounds as blocked
}

void Grid::HandleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        entityToMove = MoveSpaceship;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        entityToMove = MoveTradingPost;
    }
    else if (IsKeyPressed(KEY_THREE)) {
        entityToMove = MoveFallenStar;
    }

    // Handle placing the selected entity on mouse click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && currentMode == ToggleMode) {
        Vector2 mousePosition = GetMousePosition();
        int gridX = static_cast<int>(mousePosition.x / cellSize);
        int gridY = static_cast<int>(mousePosition.y / cellSize);
        Vector2 newLocation = { static_cast<float>(gridX), static_cast<float>(gridY) };

        // Move the selected entity to the new location if it's not blocked
        if (!IsCellBlocked(newLocation)) {
            switch (entityToMove) {
            case MoveSpaceship:
                if (spaceship) spaceship->position = newLocation;
                break;
            case MoveTradingPost:
                if (tradingPost) tradingPost->position = newLocation;
                break;
            case MoveFallenStar:
                if (fallenStar) fallenStar->position = newLocation;
                break;
            }
            entityToMove = None; // Reset the selection
        }
    }

    // Handle cell toggling with the left mouse button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        int gridX = static_cast<int>(mousePosition.x) / cellSize;
        int gridY = static_cast<int>(mousePosition.y) / cellSize;

        if (gridX >= 0 && gridX < gridSize && gridY >= 0 && gridY < gridSize) {
            ToggleCell(gridX, gridY);
        }
    }

    // Switch modes with the right mouse button
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        switch (currentMode) {
        case ToggleMode:
            currentMode = PathFindMode;
            if (starChaser != nullptr) {
                starChaser->needsPathUpdate = true; // Trigger path recalculation
            }
            break;
        case PathFindMode:
            currentMode = ToggleMode;
            break;
        }
        
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
    placeEntity(&starChaser, [this](Vector2 pos) { return new StarChaser(pos, 10.0f, fallenStar->position, tradingPost->position, spaceship->position); });
}

void Grid::DropFallenStarAt(Vector2 position) {
    if (fallenStar != nullptr) {
        fallenStar->position = position;
    }
    else {
        fallenStar = new FallenStar(position);
    }

}

Vector2 Grid::GetFallenStarPosition() {

    return fallenStar->position;

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