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

void Board::markSurroundingCellsAsMissed(const Ship &ship) {
    for (const auto &coord: ship.getCoordinates()) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = coord.first + dx;
                int ny = coord.second + dy;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && grid[ny][nx] == 0) {
                    grid[ny][nx] = -1;
                }
            }
        }
    }
}

bool Board::shoot(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        std::cout << "Выстрел за пределы поля.\n";
        return false;
    }
    if (grid[y][x] == -1 || grid[y][x] == 2) {
        std::cout << "Сюда уже стреляли.\n";
        return false;
    }

    if (grid[y][x] == 1) {
        for (auto &ship: ships) {
            if (ship->containsPoint(x, y)) {
                ship->hit(x, y);
                grid[y][x] = 2;
                if (ship->isSunk()) {
                    std::cout << "Корабль потоплен!\n";
                    markSurroundingCellsAsMissed(*ship);
                } else {
                    std::cout << "Попадание!\n";
                }
                display(false);
                return true;
            }
        }
    }

    grid[y][x] = -1;
    std::cout << "Промах.\n";
    return false;
}

void Board::display(bool showShips) const {
    std::cout << "  ";
    for (int i = 0; i < size; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int y = 0; y < size; ++y) {
        std::cout << y << " ";
        for (int x = 0; x < size; ++x) {
            if (grid[y][x] == 0) {
                std::cout << ". ";
            } else if (grid[y][x] == -1) {
                std::cout << "* ";
            } else if (grid[y][x] == 1 && showShips) {
                std::cout << "S ";
            } else if (grid[y][x] == 2) {
                std::cout << (showShips ? "X " : "Z ");
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

void Board::displayRow(int y, bool showShips) const {
    for (int x = 0; x < size; ++x) {
        if (grid[y][x] == 0) {
            std::cout << ". ";
        } else if (grid[y][x] == -1) {
            std::cout << "* ";
        } else if (grid[y][x] == 1) {
            if (showShips) {
                std::cout << "S ";
            } else {
                std::cout << ". ";
            }
        } else if (grid[y][x] == 2) {
            std::cout << (showShips ? "X " : "Z ");
        }
    }
}

bool Board::isGameOver() const {
    for (const auto &ship: ships) {
        if (!ship->isSunk()) return false;
    }
    return true;
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

bool Board::canPlaceShip(int x, int y, int length, bool horizontal) const {
    for (int offset = 0; offset < length; ++offset) {
        int curX = x + (horizontal ? offset : 0);
        int curY = y + (horizontal ? 0 : offset);

        if (curX < 0 || curX >= size || curY < 0 || curY >= size) return false;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = curX + dx;
                int ny = curY + dy;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && grid[ny][nx] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}
