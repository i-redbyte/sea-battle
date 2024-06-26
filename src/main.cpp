#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

void clearInputStream() {
    HumanPlayer::clearInputStream();
}

void printRules() {
    std::cout
            << "Правила игры 'Морской бой':"
            << std::endl;
    std::cout
            << "1. Игра проходит на поле 10x10."
            << std::endl;
    std::cout
            << "2. У вас есть 4 однопалубных, 3 двухпалубных, 2 трехпалубных и 1 четырехпалубный корабль для расстановки."
            << std::endl;
    std::cout << "3. Введите координаты (x y) и ориентацию (h - горизонтально, v - вертикально) для каждого корабля."
              << std::endl;
    std::cout
            << "4. После расстановки всех кораблей начнется бой с компьютером."
            << std::endl;
    std::cout
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            << std::endl;
}

void placeShipsManually(HumanPlayer &player, Board &board) {
    int shipsToPlace[4] = {4, 3, 2, 1};

    for (int i = 0; i < 4; ++i) {
        while (shipsToPlace[i] > 0) {
            board.display(true);
            std::cout << "Осталось расставить " << shipsToPlace[i] << " " << (i + 1) << "-палубных кораблей."
                      << std::endl;
            int x, y;
            char orientation;
            if (i != 0) {
                std::cout << "Введите координаты и ориентацию для " << (i + 1) << "-палубного корабля: ";
                std::cin >> x >> y >> orientation;

            } else {
                std::cout << "Введите только координаты для 1-палубного корабля: ";
                std::cin >> x >> y;
                orientation = 'h';
            }
            bool horizontal = orientation == 'h' || orientation == 'H';
            if (board.canPlaceShip(x, y, i + 1, horizontal) && board.placeShip(x, y, i + 1, horizontal)) {
                shipsToPlace[i]--;
            } else {
                std::cout << "Невозможно разместить корабль. Попробуйте еще раз." << std::endl;
                clearInputStream();
            }
        }
    }
}

int main() {
    printRules();

    Board humanBoard(10), aiBoard(10);
    HumanPlayer humanPlayer("Игрок");
    AIPlayer aiPlayer("Компьютер");

    char choice;
    std::cout << "Выберите режим расстановки кораблей: (m) вручную, (a) автоматически: ";
    std::cin >> choice;
    if (choice == 'm' || choice == 'M') {
        placeShipsManually(humanPlayer, humanBoard);
    } else if (choice == 'a' || choice == 'A') {
        humanPlayer.placeShips(humanBoard);
    } else {
        std::cout << "Неверный выбор. Выход из программы.\n";
        return 1;
    }

    aiPlayer.placeShips(aiBoard);

    std::cout << "Начало игры 'Морской бой'!\n";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    bool isHumanTurn = std::rand() % 2 == 0;

    while (!humanBoard.isGameOver() && !aiBoard.isGameOver()) {
        std::cout << "\nПоле противника:\t\t\tВаше поле:\n";
        for (int y = 0; y < humanBoard.getSize(); ++y) {
            aiBoard.displayRow(y, false);
            std::cout << "\t";
            humanBoard.displayRow(y, true);
            std::cout << "\n";
        }

        if (isHumanTurn) {
            std::cout << "Ваш ход.\n";
            humanPlayer.makeMove(aiBoard);
        } else {
            std::cout << "Ход компьютера.\n";
            aiPlayer.makeMove(humanBoard);
        }
        if (humanBoard.isGameOver() || aiBoard.isGameOver()) break;
        isHumanTurn = !isHumanTurn;
    }

    if (humanBoard.isGameOver()) {
        std::cout << "Победил компьютер!\n";
    } else {
        std::cout << "Поздравляем, вы победили!\n";
    }

    return 0;
}
