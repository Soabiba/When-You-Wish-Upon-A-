#include "Level.h"

void Starchaser::Update(Grid& /*grid*/) {
    switch (state) {
    case State::SearchingForStar:
        // Pathfind to Fallen Star
        break;
    case State::DeliveringStar:
        // Pathfind to Trading Post
        break;
    case State::SellingStar:
        // Handle selling the star
        break;
    case State::Resting:
        // Pathfind to Spaceship
        break;
    }
    // Other logic...
}