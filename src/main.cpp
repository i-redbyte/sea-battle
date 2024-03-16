#include <iostream>
#include <limits>
#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printRules() {
    std::cout << "Правила игры 'Морской бой':" << std::endl;
    std::cout << "1. Игра проходит на поле 10x10." << std::endl;
    std::cout << "2. У вас есть 4 однопалубных, 3 двухпалубных, 2 трехпалубных и 1 четырехпалубный корабль для расстановки." << std::endl;
    std::cout << "3. Введите координаты (x y) и ориентацию (h - горизонтально, v - вертикально) для каждого корабля." << std::endl;
    std::cout << "4. После расстановки всех кораблей начнется бой с компьютером." << std::endl;
    std::cout << "Управление: введите 'r' для перестановки кораблей, 'b' для начала боя." << std::endl;
}

void placeShipsManually(HumanPlayer& player, Board& board) {
    int shipsToPlace[4] = {4, 3, 2, 1};

    for (int i = 0; i < 4; ++i) {
        while (shipsToPlace[i] > 0) {
            board.display();
            std::cout << "Осталось расставить " << shipsToPlace[i] << " " << (i+1) << "-палубных кораблей." << std::endl;
            std::cout << "Введите координаты и ориентацию для " << (i+1) << "-палубного корабля: ";
            int x, y;
            char orientation;
            std::cin >> x >> y >> orientation;
            bool horizontal = orientation == 'h' || orientation == 'H';

            if (board.placeShip(x, y, i + 1, horizontal)) {
                shipsToPlace[i]--;
            } else {
                std::cout << "Невозможно разместить корабль. Попробуйте еще раз." << std::endl;
                clearInputStream(); // Очистка входного потока в случае неверного ввода
            }
        }
    }
}

int main() {

    return 0;
}
