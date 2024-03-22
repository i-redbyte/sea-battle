#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include <vector>
#include <memory>

class Board {
public:
    explicit Board(int size = 10);

    bool placeShip(int x, int y, int length, bool horizontal);

    bool shoot(int x, int y);

    void markSurroundingCellsAsMissed(const Ship &ship);

    void display(bool showShips) const;

    void displayRow(int y, bool showShips) const;

    [[nodiscard]] bool isGameOver() const;

    [[nodiscard]] int getSize() const { return size; }

    [[nodiscard]] bool canPlaceShip(int x, int y, int length, bool horizontal) const;

    [[nodiscard]] bool hasBeenShot(int x, int y) const;

    [[nodiscard]] bool isNextToHit(int x, int y) const;

private:
    int size;
    std::vector<std::vector<int>> grid;
    std::vector<std::shared_ptr<Ship>> ships;

    [[nodiscard]] bool checkPlacement(int x, int y, int length, bool horizontal) const;
};

#endif // BOARD_H
