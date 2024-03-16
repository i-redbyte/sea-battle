#include "Ship.h"

Ship::Ship(int length, int x, int y, bool horizontal) {
    for (int i = 0; i < length; ++i) {
        if (horizontal) {
            coordinates.push_back({x + i, y});
        } else {
            coordinates.push_back({x, y + i});
        }
        hits.push_back(false);
    }
}

bool Ship::isSunk() const {
    for (const auto& hit : hits) {
        if (!hit) return false;
    }
    return true;
}

bool Ship::containsPoint(int x, int y) const {
    return std::find(coordinates.begin(), coordinates.end(), std::make_pair(x, y)) != coordinates.end();
}

bool Ship::hit(int x, int y) {
    for (size_t i = 0; i < coordinates.size(); ++i) {
        if (coordinates[i] == std::make_pair(x, y)) {
            hits[i] = true;
            return true;
        }
    }
    return false;
}

const std::vector<std::pair<int, int>>& Ship::getCoordinates() const {
    return coordinates;
}
