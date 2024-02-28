#include "Level.h"

void StarChaser::Update(Grid& grid) {
    Vector2 target = position;

    if (needsPathUpdate) {
        switch (state) {
        case SearchingForStar:
            target = grid.GetFallenStarPosition(); // Corrected
            break;
        case DeliveringStar:
            target = grid.GetTradingPostPosition(); // Corrected
            break;
        case Resting:
            target = grid.GetSpaceshipPosition(); // Corrected
            break;
        }
        currentPath = AStarSearch(grid, position, target); 
        needsPathUpdate = false;
    }
    // Move along the path if there's a path to follow
    if (!currentPath.empty()) {
        std::cout << "Path size: " << currentPath.size() << std::endl;
        Vector2 nextStep = currentPath.front();
        MoveTowards(nextStep); 
        if (Vector2Equals(position, nextStep, 0.001f)) { 
            currentPath.erase(currentPath.begin()); 

            if (state == CarryingStar) {
                stamina -= staminaCostPerStep; // Deduct stamina for carrying the star
                if (stamina <= 0) {
                    DropStar(grid); // Logic to drop the star and change state
                }
            }
        }
    }

    // State-specific actions
    switch (state) {
    case SearchingForStar:
        if (Vector2Equals(position, grid.GetFallenStarPosition(), 0.001f)) {
            PickUpStar(grid);
            state = CarryingStar;
            needsPathUpdate = true; // Recalculate path to next objective
        }
        break;
    case DeliveringStar:
        if (Vector2Equals(position, grid.GetTradingPostPosition(), 0.001f)) {
            DeliverStar(); 
            needsPathUpdate = true;
        }
        break;
    case Resting:
        if (stamina < maxStamina) {
            Rest(); // Replenish stamina
        }
        if (Vector2Equals(position, grid.GetSpaceshipPosition(), 0.001f)) {
            state = SearchingForStar; // Go back to searching after resting
            needsPathUpdate = true;
        }
        break;
    }
}


void StarChaser::Draw() {
    int pixelX = static_cast<int>(position.x) * Grid::cellSize + Grid::cellSize / 2;
    int pixelY = static_cast<int>(position.y) * Grid::cellSize + Grid::cellSize / 2;

    DrawCircle(pixelX, pixelY, Grid::cellSize / 4, PURPLE);
}

void StarChaser::MoveTowards(Vector2 destination) {
    std::cout << "Moving towards: " << destination.x << ", " << destination.y << std::endl;
    //std::cout << "Before Move - Position: " << position.x << ", " << position.y << std::endl; // Debug print
    float stepSize = 1.0f; 
    Vector2 direction = Vector2Subtract(destination, position);
    direction = Vector2Normalize(direction);
    position = Vector2Add(position, Vector2Scale(direction, stepSize));
    //std::cout << "After Move - Position: " << position.x << ", " << position.y << std::endl; // Debug print

    // Clamp the position to the destination to avoid overshooting
    if (Vector2Distance(position, destination) < stepSize) {
        position = destination;
    }

}

void StarChaser::DeliverStar() {
    state = Resting;
}

void StarChaser::SearchForStar() {
    MoveTowards(starPosition);
    if (Vector2Distance(position, starPosition) < 0.5f) { // Threshold for "reaching" the star
        std::cout << "State Change: CarryingStar" << std::endl; // Debug print
        state = CarryingStar;
    }
}

void StarChaser::MoveToDestination(Vector2 destination) {
    MoveTowards(destination);
    // moving towards the trading post
    if (state == CarryingStar && Vector2Distance(position, tradingPostPosition) < 0.1f) {
        state = DeliveringStar;
    }
}

void StarChaser::Rest() {
    // Logic for resting
    stamina += 10.0f; 
    if (stamina >= 100.0f) { 
        stamina = 100.0f;
        state = SearchingForStar; // Return to searching after resting
    }
}

void StarChaser::DropStar(Grid& grid) {
    if (carryingStar) {
        grid.DropFallenStarAt(position);
        carryingStar = false;
        state = Resting;
    }
}

void StarChaser::PickUpStar(Grid& grid) {
    // Update the StarChaser's state to indicate it's now carrying the star
    carryingStar = true;
    grid.RemoveFallenStar();
}
