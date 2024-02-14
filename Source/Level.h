#pragma once
#include"raylib.h"
#include "raymath.h"
#include<vector>

struct Cell {
    bool blocked;
    // Add more properties as needed
};

class Grid {
public:
    Grid(int width, int height) {
        // Initialize grid with random blocked status
    }

    void draw() {
        // Use Raylib to draw the grid
    }

private:
    int width, height;
    std::vector<std::vector<Cell>> cells;
};

class Entity {
public:
    Vector2 position; // Raylib's Vector2 for position
    // Common functionalities like draw()
};

class StarChaser : public Entity {
    // Specific functionalities
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