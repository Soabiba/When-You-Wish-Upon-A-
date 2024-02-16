#pragma once
#include"raylib.h"
#include "raymath.h"
#include<vector>

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
};

enum class State {
    SearchingForStar,
    DeliveringStar,
};

class StarChaser : public Entity {
public:
    void update() {
        switch (state) {
        case State::SearchingForStar:
            // Implement logic
            break;
            // Handle other states
        }
    }
private:
    State state;
};

