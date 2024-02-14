#pragma once
#include"raylib.h"
#include "raymath.h"
#include<vector>

const int screenWidth = 800;
const int screenHeight = 600;
const int gridSize = 10; // Size of the grid (10x10 for simplicity)
const int cellSize = 40; // Visual size of each cell in pixels

struct Cell {
    bool blocked;
    // Add more properties as needed
};

class Grid {
public:
    static const int gridSize = 10; // Making it static for simplicity
    static const int cellSize = 40;
    Cell cells[gridSize][gridSize];

    Grid(); // Constructor
    void Initialize();
    void Draw();
    void Update();
    void ToggleCell(int x, int y); // For toggling cell state
};

class Entity {
public:
    Vector2 position; // Raylib's Vector2 for position
    // Common functionalities like draw()
};

enum class State {
    SearchingForStar,
    DeliveringStar,
    // Add more states
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