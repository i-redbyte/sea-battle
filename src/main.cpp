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
    std::cout
            << "2. У вас есть 4 однопалубных, 3 двухпалубных, 2 трехпалубных и 1 четырехпалубный корабль для расстановки."
            << std::endl;
    std::cout << "3. Введите координаты (x y) и ориентацию (h - горизонтально, v - вертикально) для каждого корабля."
              << std::endl;
    std::cout << "4. После расстановки всех кораблей начнется бой с компьютером." << std::endl;
    std::cout << "Управление: введите 'r' для перестановки кораблей, 'b' для начала боя." << std::endl;
}

void placeShipsManually(HumanPlayer &player, Board &board) {
    int shipsToPlace[4] = {4, 3, 2, 1};

    for (int i = 0; i < 4; ++i) {
        while (shipsToPlace[i] > 0) {
            board.display(true);
            std::cout << "Осталось расставить " << shipsToPlace[i] << " " << (i + 1) << "-палубных кораблей."
                      << std::endl;
            std::cout << "Введите координаты и ориентацию для " << (i + 1) << "-палубного корабля: ";
            int x, y;
            char orientation;
            std::cin >> x >> y >> orientation;
            bool horizontal = orientation == 'h' || orientation == 'H';

            if (board.placeShip(x, y, i + 1, horizontal)) {
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

//    humanPlayer.placeShips(humanBoard);
    placeShipsManually(humanPlayer, humanBoard);
    aiPlayer.placeShips(aiBoard);

    std::cout << "Начало игры 'Морской бой'!\n";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    bool isHumanTurn = std::rand() % 2 == 0;

    while (!humanBoard.isGameOver() && !aiBoard.isGameOver()) {
        std::cout << "\nПоле противника:\t\t\tВаше поле:\n";
        for (int y = 0; y < humanBoard.getSize(); ++y) {
            // Вывод строки поля противника (без показа кораблей)
            aiBoard.displayRow(y, false);
            std::cout << "\t";
            // Вывод строки своего поля (с показом кораблей)
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

        isHumanTurn = !isHumanTurn; // Смена очереди хода
    }

    if (humanBoard.isGameOver()) {
        std::cout << "Победил компьютер!\n";
    } else {
        std::cout << "Поздравляем, вы победили!\n";
    }

    return 0;
}

//int main() {
//    printRules();
//
//    Board humanBoard(10), aiBoard(10);
//    HumanPlayer humanPlayer("Игрок");
//    AIPlayer aiPlayer("Компьютер");
//
////    placeShipsManually(humanPlayer, humanBoard);
//    aiPlayer.placeShips(aiBoard);
//    humanPlayer.placeShips(humanBoard);
//    std::cout << "Нажмите 'b' для начала боя: ";
//    char startGame;
//    std::cin >> startGame;
//    clearInputStream();
//
//    if (startGame != 'b' && startGame != 'B') {
//        std::cout << "Игра окончена." << std::endl;
//        return 0;
//    }
//
//    std::srand(static_cast<unsigned int>(std::time(nullptr)));
//    bool isHumanTurn = std::rand() % 2 == 0;
//
//    while (!humanBoard.isGameOver() && !aiBoard.isGameOver()) {
//        if (isHumanTurn) {
//            std::cout << "Ваш ход." << std::endl;
//            humanPlayer.makeMove(aiBoard);
//        } else {
//            std::cout << "Ход компьютера." << std::endl;
//            aiPlayer.makeMove(humanBoard);
//        }
//
//        isHumanTurn = !isHumanTurn;
//    }
//
//    if (humanBoard.isGameOver()) {
//        std::cout << "Компьютер выиграл!" << std::endl;
//    } else {
//        std::cout << "Поздравляем, вы выиграли!" << std::endl;
//    }
//
//    return 0;
//}

