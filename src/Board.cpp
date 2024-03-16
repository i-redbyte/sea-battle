#include "Board.h"
#include <iostream>

Board::Board(int size) : size(size) {
    grid = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

bool Board::placeShip(int x, int y, int length, bool horizontal) {
    if (!checkPlacement(x, y, length, horizontal)) return false;

    auto ship = std::make_shared<Ship>(length, x, y, horizontal);
    ships.push_back(ship);

    for (const auto &coord: ship->getCoordinates()) {
        grid[coord.second][coord.first] = 1;
    }
    return true;
}

bool Board::shoot(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        std::cout << "Shot out of bounds.\n";
        return false;
    }
    if (grid[y][x] == -1) {
        std::cout << "Location already shot.\n";
        return false;
    }

    for (auto &ship: ships) {
        if (ship->containsPoint(x, y)) {
            ship->hit(x, y);
            grid[y][x] = -1; // Отмечаем попадание
            std::cout << (ship->isSunk() ? "Ship sunk!\n" : "Hit!\n");
            return true;
        }
    }

    grid[y][x] = -1; // Отмечаем промах
    std::cout << "Miss.\n";
    return false;
}

void Board::display() const {
    for (const auto &row: grid) {
        for (int cell: row) {
            switch (cell) {
                case 1:
                    std::cout << "S ";
                    break;
                case -1:
                    std::cout << "* ";
                    break;
                default:
                    std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

bool Board::isGameOver() const {
    for (const auto &ship: ships) {
        if (!ship->isSunk()) return false; // Если есть хотя бы один непотопленный корабль, игра продолжается
    }
    return true; // Все корабли потоплены
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