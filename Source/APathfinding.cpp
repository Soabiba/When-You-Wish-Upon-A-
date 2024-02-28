#include "Level.h"

std::vector<Vector2> ReconstructPath(AStarNode* targetNode);

bool Vector2Equals(const Vector2& v1, const Vector2& v2, float tolerance) {
    return (std::fabs(v1.x - v2.x) < tolerance) && (std::fabs(v1.y - v2.y) < tolerance);
}

std::vector<Vector2> AStarSearch(const Grid& grid, Vector2 start, Vector2 target) {
    std::map<Vector2, AStarNode, Vector2Compare> allNodes; 
    std::vector<AStarNode*> openSet;
    std::set<Vector2, Vector2Compare> closedSet; 

    AStarNode* startNode = &allNodes[start];
    startNode->gCost = 0;
    startNode->hCost = Vector2Distance(start, target);
    openSet.push_back(startNode);

    while (!openSet.empty()) {
        AStarNode* currentNode = *std::min_element(openSet.begin(), openSet.end(), [](const AStarNode* a, const AStarNode* b) { return a->fCost() < b->fCost(); });

        if (Vector2Equals(currentNode->position, target, 0.001f)) {
            return ReconstructPath(currentNode);
        }

        openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
        closedSet.insert(currentNode->position);

        for (Vector2 dir : GetNeighborDirections()) {
            Vector2 neighborPos = Vector2Add(currentNode->position, dir);
            if (!grid.IsCellBlocked(neighborPos) && closedSet.find(neighborPos) == closedSet.end()) {
                AStarNode* neighborNode = &allNodes[neighborPos];
                float tentativeGCost = currentNode->gCost + Vector2Distance(currentNode->position, neighborPos);

                if (tentativeGCost < neighborNode->gCost) {
                    neighborNode->parent = currentNode;
                    neighborNode->gCost = tentativeGCost;
                    neighborNode->hCost = Vector2Distance(neighborPos, target);

                    if (std::find(openSet.begin(), openSet.end(), neighborNode) == openSet.end()) {
                        openSet.push_back(neighborNode);
                    }
                }
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

std::vector<Vector2> ReconstructPath(AStarNode* targetNode) {
    std::vector<Vector2> path;
    AStarNode* currentNode = targetNode;
    while (currentNode != nullptr) {
        path.push_back(currentNode->position);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end()); // Reverse to get the path from start to target
    return path;
}


std::vector<Vector2> GetNeighborDirections() {
    return { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };
}