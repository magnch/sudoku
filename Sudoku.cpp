#include "Sudoku.h"

// Default-konstruktør for spillbrettet
Sudoku::Sudoku() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            this->board[row][col] = 0;
        }
    }
}

// Konstruktør som oppretter spillbrettet basert på et eksisterende array
Sudoku::Sudoku(int board[9][9]) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            this->board[row][col] = board[row][col];
        }
    }
}

// Printer ut spillbrettet til terminal
void Sudoku::print_board() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            std::cout << board[row][col] << " ";
            if(col == 2 || col == 5){
                std::cout << "| ";
            }
        }
        if(row == 2 || row == 5){
            std::cout << std::endl;
            std::cout << "---------------------";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Sjekker om en rad er gyldig
bool Sudoku::check_row(int row) {

    bool seen[10] = {false}; // Array to track numbers 1-9 (index 0 is unused)

    for (int col = 0; col < num_cols; col++) {
        int num = board[row][col];
        if (num) { // Ignore empty tiles
            if (seen[num]) {
                std::cout << "Row " << row + 1 << " not valid" << std::endl;
                return false; // Duplicate found
            }
            seen[num] = true;
        }
    }
    return true; // No duplicates found
}

// Sjekker om en kolonne er gyldig
bool Sudoku::check_col(int col) {

    bool seen[10] = {false}; // Array to track numbers 1-9 (index 0 is unused)

    for (int row = 0; row < num_rows; row++) {
        int num = board[row][col];
        if (num) { // Ignore empty tiles
            if (seen[num]) {
                std::cout << "Column " << col + 1 << " not valid" << std::endl;
                return false; // Duplicate found
            }
            seen[num] = true;
        }
    }
    return true; // No duplicates found
}

// Sjekker om en boks (3x3 seksjon) er gyldig
bool Sudoku::check_box(int box) {
    bool seen[10] = {false};
    int start_row = (box/3) * 3;
    int start_col = (box%3) * 3;
    for (int row = start_row; row < start_row + 3; row++) {
        for (int col = start_col; col < start_col + 3; col++) {
            int num = board[row][col];
            if (num) {
                if (seen[num]) {
                    std::cout << "Box " << box + 1 << " not valid" << std::endl;
                    return false; // Duplicate found
                }
                seen[num] = true;
            }
        }
    }
    return true;
}

// Lagrer spillbrettet til spesifisert tekstfil
void Sudoku::save_board_to_file(std::string filename){
    std::filesystem::path save_file{filename};
    std::ofstream ofs{save_file};
    if(!ofs) {
        throw std::ios_base::failure("Could not open file: " + filename);
    }

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            ofs << board[row][col] << " ";
        }
        ofs << '\n';
    }
}

// Laster inn et spillbrett fra spesifisert tekstfil
void Sudoku::load_board_from_file(std::string filename) {
    std::filesystem::path load_file{filename};
    std::ifstream ifs{load_file};
    if(!ifs) {
        throw std::ios_base::failure("Could not open file: " + filename);
    }
    int num;

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            ifs >> num;
            set_cell(row, col, num);
        }
    }
}

// Sjekker om hele brettet er gyldig
bool Sudoku::check_board() {
    for (int i = 0; i < num_rows; i++) {
        if(!check_row(i) || !check_col(i) || !check_box(i)) {
            std::cout << "Board not valid" << std::endl;
            return false;
        }
    }
    return true;
}

// Sjekker om hele brettet er fylt inn
bool Sudoku::check_complete() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            if(!board[row][col]) {
                std::cout << "Board incomplete" << std::endl;
                return false;
            }
        }
    }
    return true;
}