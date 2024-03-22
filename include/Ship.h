#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <utility>

class Ship {
public:
    Ship(int length, int x, int y, bool horizontal);

    [[nodiscard]] bool isSunk() const;

    [[nodiscard]] bool containsPoint(int x, int y) const;

    bool hit(int x, int y);

    [[nodiscard]] const std::vector<std::pair<int, int>>& getCoordinates() const;

private:
    std::vector<std::pair<int, int>> coordinates;
    std::vector<bool> hits;
};

#endif // SHIP_H
