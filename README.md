# Grid-Based StarChaser Game

## Overview
This project is a grid-based simulation where an entity known as the `StarChaser` navigates through a world filled with obstacles, collects a fallen star, trades it at a trading post, and returns to its spaceship to rest. The simulation showcases pathfinding algorithms, state management, and simple game mechanics.

## Features
- **Dynamic Grid World**: A 2D grid world where each cell can be toggled between blocked and unblocked states.
- **Entities**: Includes the `Spaceship`, `Trading Post`, `Fallen Star`, and the `StarChaser`.
- **Pathfinding**: The `StarChaser` uses the A* algorithm to find the shortest path to its current objective.
- **State Management**: The `StarChaser` operates under a finite state machine with states for searching, carrying the star, delivering, and resting.
- **Interactive Mode Switching**: Users can toggle between editing the grid and observing the `StarChaser` in action.

## How to Run
Ensure you have [Raylib](https://www.raylib.com/) installed and properly set up in your development environment, as this project relies on it for rendering and input handling.

1. Clone this repository to your local machine.
2. Open the project in your preferred IDE or editor that supports C/C++ development.
3. Build and run the project.

## Controls
- **Left Mouse Button**: Toggle the state of grid cells between blocked and unblocked.
- **Right Mouse Button**: Switch between edit mode (allowing cell state toggling) and pathfinding mode (where the `StarChaser` acts according to its AI).

## Implementation Details
- **Pathfinding**: Implemented using the A* algorithm to navigate around obstacles.
- **State Machine**: The `StarChaser`'s behavior is dictated by a finite state machine, responding dynamically to changes in the environment and its own state.
