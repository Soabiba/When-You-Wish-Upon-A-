#include "Level.h"

void StarChaser::Update() {
    starPosition = grid->GetFallenStarPosition();
    tradingPostPosition = grid->GetTradingPostPosition();
    spaceshipPosition = grid->GetSpaceshipPosition();

    switch (state) {
    case SearchingForStar:
        SearchForStar();
        break;
    case CarryingStar:
        MoveToDestination();
        break;
    case DeliveringStar:
        DeliverStar();
        break;
    case Resting:
        Rest();
        break;
    }
}

void StarChaser::Draw() {
    int pixelX = static_cast<int>(position.x) * Grid::cellSize + Grid::cellSize / 2;
    int pixelY = static_cast<int>(position.y) * Grid::cellSize + Grid::cellSize / 2;

    DrawCircle(pixelX, pixelY, Grid::cellSize / 4, PURPLE);
}

void StarChaser::DeliverStar() {
    // Example logic for searching for the star
    // This might involve checking the distance to the starPosition and moving towards it
    // or updating the state if the star is reached.
}

void StarChaser::SearchForStar() {
    // Example logic for searching for the star
    // This might involve checking the distance to the starPosition and moving towards it
    // or updating the state if the star is reached.
}

void StarChaser::MoveToDestination() {
    // Example logic for searching for the star
    // This might involve checking the distance to the starPosition and moving towards it
    // or updating the state if the star is reached.
}

void StarChaser::Rest() {
    // Example logic for searching for the star
    // This might involve checking the distance to the starPosition and moving towards it
    // or updating the state if the star is reached.
}