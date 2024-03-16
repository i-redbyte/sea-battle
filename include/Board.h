#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board(int size = 10);
    bool placeShip(int x, int y, int length, bool horizontal);
    bool shoot(int x, int y);
    void display();
    bool isGameOver();

private:
    std::vector<std::vector<int>> grid;
    int size;
    int shipsCount;
    bool checkPlacement(int x, int y, int length, bool horizontal) const;
};

#endif // BOARD_H
