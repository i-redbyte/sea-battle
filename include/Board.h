#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include <vector>
#include <memory>

class Board {
public:
    Board(int size = 10);

    bool placeShip(int x, int y, int length, bool horizontal);

    bool shoot(int x, int y);

    void display() const;

    bool isGameOver() const;

private:
    int size;
    std::vector<std::vector<int>> grid;
    std::vector<std::shared_ptr<Ship>> ships;

    bool checkPlacement(int x, int y, int length, bool horizontal) const;
};

#endif // BOARD_H
