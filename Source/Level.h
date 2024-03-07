#pragma once
#include"raylib.h"
#include "raymath.h"
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <set>
#include <algorithm>

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

class StarChaser;

struct Cell {
    bool blocked;
};

class Grid {
public:
    static const int gridSize = 10;
    static const int cellSize = 40;
    Cell cells[gridSize][gridSize];

    Spaceship* spaceship = nullptr; // Pointer to a Spaceship object
    TradingPost* tradingPost = nullptr;
    FallenStar* fallenStar = nullptr;
    StarChaser* starChaser = nullptr;

    Vector2 GetFallenStarPosition();
    Vector2 GetTradingPostPosition();
    Vector2 GetSpaceshipPosition();

    void PlaceEntities();

    Grid(); // Constructor
    ~Grid(); // Destructor to clean up the spaceship

    enum Mode {
        ToggleMode,
        PathFindMode,
        MoveEntityMode,
        RemoveEntityMode
    };

    void Initialize();
    void Draw();
    void Update();
    void ToggleCell(int x, int y); // For toggling cell state
    void HandleInput();

    Mode currentMode = ToggleMode;

    void SwitchMode() {
        currentMode = (currentMode == ToggleMode) ? PathFindMode : ToggleMode;
    }

    // New method to trigger pathfinding
    void TriggerPathFind(int x, int y);
    bool IsCellOccupied(Vector2 position) const;
    bool IsCellBlocked(Vector2 position) const;
    void DropFallenStarAt(Vector2 position);

    void RemoveFallenStar() {
        delete fallenStar;
        fallenStar = nullptr;
    }

};

enum StarChaserState {
    SearchingForStar,
    CarryingStar,
    DeliveringStar,
    Resting
};

class StarChaser {
public:
    Vector2 position = { 0, 0 }; // Default position
    float stamina = 10.0f; // Default stamina value
    float maxStamina = 10.0f; // Adjust as needed
    float staminaCostPerStep = 1.0f; // Adjust as needed
    bool needsPathUpdate = true;
    StarChaserState state = SearchingForStar; // Default state
    Vector2 starPosition = { 0, 0 }; // Default position of the Fallen Star
    Vector2 tradingPostPosition = { 00, 0 }; // Default position of the Trading Post
    Vector2 spaceshipPosition = { 0, 0 }; // Default position of the Spaceship
    void MoveTowards(Vector2 destination);

    StarChaser(Vector2 pos, float initialStamina, Vector2 starPos, Vector2 tradingPostPos, Vector2 spaceshipPos)
        : position(pos), stamina(initialStamina), starPosition(starPos), tradingPostPosition(tradingPostPos), spaceshipPosition(spaceshipPos), state(SearchingForStar) {}

    void Update(Grid& grid);
    void Draw();
    void DrawStamina() const;
    void DeliverStar();
    void SearchForStar();
    void MoveToDestination(Vector2 destination);
    void Rest();
    std::vector<Vector2> currentPath;

    void DropStar(Grid& grid);

    void PickUpStar(Grid& grid);

private:
    bool carryingStar = false;
};

struct Vector2Compare {
    bool operator() (const Vector2& a, const Vector2& b) const {
        return (a.x < b.x) || (!(b.x < a.x) && a.y < b.y);
    }
};

inline float OctileDistance(Vector2 a, Vector2 b) {
    float D = 1.0f; // Cost of moving horizontally or vertically
    float D2 = std::sqrt(2.0f); // Cost of moving diagonally
    float dx = std::abs(a.x - b.x);
    float dy = std::abs(a.y - b.y);
    return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

struct AStarNode {
    Vector2 position;
    float gCost;
    float hCost;
    AStarNode* parent;


    AStarNode() : position({ 0, 0 }), gCost(INFINITY), hCost(INFINITY), parent(nullptr) {}
    // Constructor with initialization
    AStarNode(Vector2 pos, float g = INFINITY, float h = INFINITY, AStarNode* p = nullptr)
        : position(pos), gCost(g), hCost(h), parent(p) {}

    float fCost() const { return gCost + hCost; }
};

// Utility functions
float Heuristic(Vector2 a, Vector2 b);
std::vector<Vector2> GetNeighborDirections();
float Vector2Distance(Vector2 v1, Vector2 v2);

// A* pathfinding function
std::vector<Vector2> AStarSearch(const Grid& grid, Vector2 start, Vector2 target);
std::vector<Vector2> ReconstructPath(AStarNode* targetNode);

bool Vector2Equals(const Vector2& v1, const Vector2& v2, float tolerance = 0.001f);