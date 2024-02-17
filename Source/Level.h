#pragma once
#include"raylib.h"
#include "raymath.h"
#include<vector>
#include <map>

const int screenWidth = 800;
const int screenHeight = 600;
const int gridSize = 10; // Size of the grid (10x10 for simplicity)
const int cellSize = 40; // Visual size of each cell in pixels

class Spaceship {
public:
    Vector2 position; 

    // Constructor takes a Vector2 for position
    Spaceship(Vector2 pos) : position(pos) {}

    void Draw();
};

class TradingPost {
public:
    Vector2 position; 

    TradingPost(Vector2 pos) : position(pos) {}

    void Draw();
};

class FallenStar {
public:
    Vector2 position; 

    FallenStar(Vector2 pos) : position(pos) {}

    void Draw();
};

struct Cell {
    bool blocked;
};

class Grid {
public:
    static const int gridSize = 10; 
    static const int cellSize = 40;
    Cell cells[gridSize][gridSize];

    Spaceship* spaceship; // Pointer to a Spaceship object
    TradingPost* tradingPost;
    FallenStar* fallenStar;

    void PlaceEntities();

    Grid(); // Constructor
    ~Grid(); // Destructor to clean up the spaceship

    void Initialize();
    void Draw();
    void Update();
    void ToggleCell(int x, int y); // For toggling cell state
};

class Entity {
public:
    Vector2 position; 

    Entity(Vector2 pos) : position(pos) {}
};

enum class State {
    SearchingForStar,
    DeliveringStar,
    SellingStar,
    Resting
};

class Starchaser : public Entity {
public:
    Starchaser(Vector2 pos): Entity(pos),
        stamina(100),
        state(State::SearchingForStar),
        currentPosition({ 0, 0 }), 
        targetPosition({ 0, 0 }), 
        spaceshipPosition({ 0, 0 }), 
        starPosition({ 0, 0 }), 
        tradingPostPosition({ 0, 0 }), 
        carryingStar(false) { 
        // Constructor body
    }

    void Update(Grid& grid); // The grid is passed for pathfinding and interaction
    void Draw();
    void FindPath(Vector2 destination, Grid& grid); // For A* pathfinding
    void MoveAlongPath(); // Moves the Starchaser along the calculated path

private:
    int stamina;
    State state;
    std::vector<Vector2> path;
    Vector2 starPosition;
    Vector2 tradingPostPosition;
    Vector2 spaceshipPosition;

    // A* pathfinding related variables
    std::map<Vector2, float> gCost; // Cost from start to current node
    std::map<Vector2, Vector2> cameFrom; // Map to reconstruct path
    Vector2 currentPosition; // Current position on the grid
    Vector2 targetPosition; // Current target position on the grid
    bool carryingStar = false; // Is the Starchaser currently carrying the star?

    // FSM methods
    void SearchForStar(Grid& grid);
    void DeliverStar(Grid& grid);
    void SellStar(Grid& grid);
    void Rest(Grid& grid);

    // Helper methods
    float Heuristic(Vector2 a, Vector2 b); // Heuristic function for A*
    std::vector<Vector2> GetNeighbors(Vector2 node, Grid& grid); // Get neighbors for pathfinding
    void ReconstructPath(Vector2 current); // Reconstruct the path from the cameFrom map
    void ReduceStamina(); // Method to reduce stamina as the Starchaser moves
    void DropStarIfExhausted(); // Drops the star if stamina reaches zero
    void RestIfNeeded(); // Go to rest if stamina is low or star is delivered
};