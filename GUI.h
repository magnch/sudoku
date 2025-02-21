#pragma once
#include <memory>
#include "AnimationWindow.h"
#include "Tile.h"
#include "Sudoku.h"
#include "widgets/TextInput.h"

class SudokuWindow : public TDT4102::AnimationWindow
{
    private:

        // Konstanter for grafikkvinduet
        static constexpr int tile_size = 33;
        static constexpr int board_width = num_cols*tile_size;
        static constexpr int board_height = num_rows*tile_size;
        static constexpr int pad_size = 10;
        static constexpr int button_width = board_width;
        static constexpr int box_width = board_width;
        static constexpr int button_height = 40;
        static constexpr int box_height = 60;

        static constexpr int width = 2 * pad_size + board_width;
        static constexpr int height = 3 * pad_size + board_height + button_height;

        static constexpr TDT4102::Point button_pos = {pad_size + tile_size/4, 2*pad_size + board_height};
        static constexpr TDT4102::Point box_pos = {pad_size, (height-box_height)/2};


        // 2D-vektor med Tiles, som utgjør det grafiske brettet
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
        std::shared_ptr<Tile> selected_tile;

        // Øvrige GUI-elementer
        TDT4102::Button check_button;
        TDT4102::TextInput victory_box;

        // Spillbrett-objektet som kjører spillogikken
        std::shared_ptr<Sudoku> sudoku_board = std::make_shared<Sudoku>();
        bool game_started = false;
        bool won = false;


        // Medlemsfunksjoner
        std::shared_ptr<Tile>& get_tile(TDT4102::Point);
        void select_tile(std::shared_ptr<Tile>& tile);
        bool in_range(TDT4102::Point xy) const;
        void handle_input();
        void cb_click();
        void cb_check();
        void initialize_tiles();
        void set_tiles();
        void toggle_visible(bool visible);
        void draw_grid();

    public:
        // konstruktør
        SudokuWindow(int x, int y, const std::string& title);
        // kjører programmet
        void run(std::string board_filename);

};