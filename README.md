# Grid-Based StarChaser Game

## Overview
This project is a grid-based simulation where an entity known as the `StarChaser` navigates through a world filled with obstacles, collects a fallen star, trades it at a trading post, and returns to its spaceship to rest. The simulation showcases pathfinding algorithms, state management, and simple game mechanics.

## Features
- **Dynamic Grid World**: Interactive 2D grid where cells can be dynamically toggled between blocked and unblocked states.
- **Entities**: The simulation includes a `Spaceship`, `Trading Post`, `Fallen Star`, and the `StarChaser` as interactive entities within the world.
- **Pathfinding**: Utilizes the A* algorithm to navigate the `StarChaser` around obstacles to its current objective.
- **State Management**: Manages the `StarChaser`'s behavior with a finite state machine, handling states for searching, carrying the star, delivering, and resting.
- **Interactive Editing**: Allows users to toggle the world's state, move entities, and observe the `StarChaser` in action in real-time.
- **Entity Repositioning**: In toggle mode, users can reposition the `Spaceship`, `Trading Post`, and `Fallen Star` to new locations within the grid.

## Getting Started
To start the game right click.
Ensure [Raylib](https://www.raylib.com/) is installed and set up in your development environment, as this project relies on it for graphical rendering and input handling.

### Installation
1. Clone this repository to your local machine.
2. Open the project in an IDE or editor that supports C/C++ development.
3. Build and run the project according to your IDE's or compiler's instructions.

## Controls
- **Left Mouse Button**: Toggle cells between blocked and unblocked. Place selected entities in new locations.
- **Right Mouse Button**: Switch between edit mode (cell toggling and entity placement) and simulation mode (observe `StarChaser` actions).
- **1, 2, 3 Keys**: Select the `Spaceship`, `Trading Post`, and `Fallen Star` respectively for repositioning in toggle mode.

## Implementation Details
- **Pathfinding**: Implemented using the A* algorithm to navigate around obstacles.
- **State Machine**: The `StarChaser`'s behavior is dictated by a finite state machine, responding dynamically to changes in the environment and its own state.
