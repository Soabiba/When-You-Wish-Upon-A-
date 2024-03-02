#include "Level.h"

std::vector<Vector2> ReconstructPath(AStarNode* targetNode);

bool Vector2Equals(const Vector2& v1, const Vector2& v2, float tolerance) {
    return (std::fabs(v1.x - v2.x) < tolerance) && (std::fabs(v1.y - v2.y) < tolerance);
}

float Heuristic(Vector2 a, Vector2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Vector2> AStarSearch(const Grid& grid, Vector2 start, Vector2 target) {
    std::map<Vector2, AStarNode, Vector2Compare> allNodes;
    std::vector<AStarNode*> openSet;
    std::set<Vector2, Vector2Compare> closedSet;
    std::cout << "A* Search started from [" << start.x << ", " << start.y << "] to [" << target.x << ", " << target.y << "]\n";

    AStarNode* startNode = &allNodes[start];
    startNode->position = start;
    startNode->gCost = 0;
    startNode->hCost = Vector2Distance(start, target);
    openSet.push_back(startNode);

    std::cout << "Initial Open Set Size: " << openSet.size() << ", Closed Set Size: " << closedSet.size() << std::endl;

    while (!openSet.empty()) {
        AStarNode* currentNode = *std::min_element(openSet.begin(), openSet.end(), [](const AStarNode* a, const AStarNode* b) { return a->fCost() < b->fCost(); });

        std::cout << "Processing Node at [" << currentNode->position.x << ", " << currentNode->position.y << "], FCost: " << currentNode->fCost() << std::endl;

        if (Vector2Equals(currentNode->position, target, 0.001f)) {
            std::cout << "Path found. Reconstructing path...\n";
            return ReconstructPath(currentNode);
        }

        openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
        closedSet.insert(currentNode->position);

        for (Vector2 dir : GetNeighborDirections()) {
            Vector2 neighborPos = Vector2Add(currentNode->position, dir);
            if (!grid.IsCellBlocked(neighborPos) && closedSet.find(neighborPos) == closedSet.end()) {
                AStarNode& neighborNode = allNodes[neighborPos]; // Access or create the node
                float tentativeGCost = currentNode->gCost + Vector2Distance(currentNode->position, neighborPos);
                if (tentativeGCost < neighborNode.gCost) { // Found a better path
                    neighborNode.parent = currentNode; // Set parent to the current node
                    neighborNode.gCost = tentativeGCost; // Update gCost
                    neighborNode.hCost = Heuristic(neighborPos, target); // Update hCost
                    neighborNode.position = neighborPos; // Ensure the position is set

                    // Add to openSet if not already present
                    if (std::find(openSet.begin(), openSet.end(), &neighborNode) == openSet.end()) {
                        openSet.push_back(&neighborNode);
                    }
                }
            }
        }
    }
    std::cout << "No path found.\n";
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

