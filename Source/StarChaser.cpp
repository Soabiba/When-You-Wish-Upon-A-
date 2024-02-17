#include "Level.h"

// Constructor
Starchaser::Starchaser(Vector2 pos) : Entity(pos), stamina(100), state(State::SearchingForStar), currentPosition(pos), targetPosition({ 0, 0 }), carryingStar(false) {
    
}

// Update method - the core FSM logic
void Starchaser::Update(Grid& grid) {
    switch (state) {
    case State::SearchingForStar:
        SearchForStar(grid);
        break;
    case State::DeliveringStar:
        DeliverStar(grid);
        break;
    case State::SellingStar:
        SellStar(grid);
        break;
    case State::Resting:
        Rest(grid);
        break;
    }

    // Handle moving along the path if one exists
    if (!path.empty()) {
        MoveAlongPath();
    }

    // Check for stamina and potentially drop the star or rest
    RestIfNeeded();
}

// Stub for the Draw method
void Starchaser::Draw() {
    
    DrawCircleV(currentPosition, 10, BLUE); 
}

// Stub for the FindPath method using A* pathfinding
void Starchaser::FindPath(Vector2 destination, Grid& grid) {
    
}

// Stub for the MoveAlongPath method
void Starchaser::MoveAlongPath() {
    
    ReduceStamina();
    
}

// FSM state methods
void Starchaser::SearchForStar(Grid& grid) {
    
}

void Starchaser::DeliverStar(Grid& grid) {
    // Placeholder: Implement logic to deliver the star to the trading post
}

void Starchaser::SellStar(Grid& grid) {
    // Placeholder: Implement logic for selling the star at the trading post
}

void Starchaser::Rest(Grid& grid) {
    // Placeholder: Implement logic for resting (e.g., moving to the spaceship)
}

// Helper methods
float Starchaser::Heuristic(Vector2 a, Vector2 b) {
    
    return Vector2Distance(a, b); 
}

std::vector<Vector2> Starchaser::GetNeighbors(Vector2 node, Grid& grid) {
    // Placeholder: Return a list of walkable neighbor tiles for the given node
}

void Starchaser::ReconstructPath(Vector2 current) {
    // Placeholder: Reconstruct the path from the `cameFrom` map
}

void Starchaser::ReduceStamina() {
    // Placeholder: Reduce stamina and handle exhaustion
}

void Starchaser::DropStarIfExhausted() {
    // Placeholder: Drop the star if stamina reaches zero
}

void Starchaser::RestIfNeeded() {
    // Placeholder: Check if the Starchaser needs to rest and update state accordingly
}
