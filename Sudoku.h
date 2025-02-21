#pragma once
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <filesystem>

constexpr int num_rows = 9;
constexpr int num_cols = 9;


class Sudoku {
    private:
        int board[9][9];
    public:
        Sudoku();
        Sudoku(int board[9][9]);

        void set_cell(int row, int col, int num) {board[row][col] = num;}
        int get_cell(int row, int col) { return board[row][col];}
        void save_board_to_file(std::string filename);
        void load_board_from_file(std::string filename);
        void print_board();

        bool check_row(int row);
        bool check_col(int col);
        bool check_box(int box);
        bool check_board();
        bool check_complete();

};