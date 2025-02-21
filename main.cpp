#include "Sudoku.h"
#include "GUI.h"

int main() {

	TDT4102::Point start_point{200, 300};

    SudokuWindow sw{start_point.x, start_point.y, "Sudoku"};
    sw.run("game-files/easy.txt");

    return 0;
}