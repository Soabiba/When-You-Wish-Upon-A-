#pragma once
#include"raylib.h"
#include "raymath.h"
#include <cmath>
#include <queue>
#include<vector>
#include <map>
#include <unordered_map>

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

    Vector2 GetFallenStarPosition();
    Vector2 GetTradingPostPosition();
    Vector2 GetSpaceshipPosition();

    Spaceship* spaceship; // Pointer to a Spaceship object
    TradingPost* tradingPost;
    FallenStar* fallenStar;
    StarChaser* starChaser;

    void PlaceEntities();

    Grid(); // Constructor
    ~Grid(); // Destructor to clean up the spaceship

    void Initialize();
    void Draw();
    void Update();
    void ToggleCell(int x, int y); // For toggling cell state
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
    float stamina = 100.0f; // Default stamina value
    StarChaserState state = SearchingForStar; // Default state
    Vector2 starPosition = { 0, 0 }; // Default position of the Fallen Star
    Vector2 tradingPostPosition = { 0, 0 }; // Default position of the Trading Post
    Vector2 spaceshipPosition = { 0, 0 }; // Default position of the Spaceship

    StarChaser(Vector2 pos, float initialStamina, Vector2 starPos, Vector2 tradingPostPos, Vector2 spaceshipPos)
        : grid(nullptr), position(pos), stamina(initialStamina), starPosition(starPos), tradingPostPosition(tradingPostPos), spaceshipPosition(spaceshipPos), state(SearchingForStar) {}

    StarChaser(Grid* grid);
    void Update();

    void Draw();
    void DeliverStar();
    void SearchForStar();
    void MoveToDestination();
    void Rest();
    // Additional methods for StarChaser behavior will go here

private:
    Grid* grid;
};