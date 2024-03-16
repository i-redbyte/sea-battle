#include "Board.h"
#include <iostream>

Board::Board(int size) : size(size), shipsCount(0) {
    grid = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

bool Board::placeShip(int x, int y, int length, bool horizontal) {
    if (!checkPlacement(x, y, length, horizontal)) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (horizontal) {
            grid[y][x + i] = 1;
        } else {
            grid[y + i][x] = 1;
        }
    }
    ++shipsCount;
    return true;
}

bool Board::shoot(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size || grid[y][x] == -1) {
        std::cout << "Invalid shot or already shot at this location.\n";
        return false;
    }

    if (grid[y][x] == 1) {
        grid[y][x] = -1;
        std::cout << "Hit!\n";
        return true;
    } else {
        grid[y][x] = -1;
        std::cout << "Miss.\n";
        return false;
    }
}

void Board::display() {
    for (const auto &row : grid) {
        for (int cell : row) {
            if (cell == 0) {
                std::cout << ". ";
            } else if (cell == -1) {
                std::cout << "* ";
            } else {
                std::cout << "S ";
            }
        }
        std::cout << "\n";
    }
}

bool Board::isGameOver() {
    // Эта функция должна проверить, все ли корабли потоплены
    return false; // Заглушка
}

bool Board::checkPlacement(int x, int y, int length, bool horizontal) const {
    if (horizontal) {
        if (x + length > size) return false;
        for (int i = 0; i < length; ++i) {
            if (grid[y][x + i] != 0) return false;
        }
    } else {
        if (y + length > size) return false;
        for (int i = 0; i < length; ++i) {
            if (grid[y + i][x] != 0) return false;
        }
    }
    return true;
}
