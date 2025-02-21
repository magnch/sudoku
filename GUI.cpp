#include "GUI.h"

// Konstruktør for grafikkvinduet
SudokuWindow::SudokuWindow(int x, int y, const std::string& title) : 
	// Initialiser medlemsvariabler, bruker konstruktøren til AnimationWindow-klassen
	AnimationWindow{x, y, width, height, title}, 
    check_button{button_pos, button_width, button_height, "Check board"},
    victory_box{box_pos, box_width, box_height, "You won!"}
    {
        // Fyller brettet med tiles
        tiles.resize(num_rows);
        for (int row = 0; row < num_rows; row++) {
            for (int col = 0; col < num_cols; col++) {
                TDT4102::Point board_pos = {row, col};
                tiles.at(row).emplace_back(new Tile{board_pos, TDT4102::Point{pad_size + col * tile_size, pad_size + row * tile_size}, tile_size});
                tiles.at(row).back()->setCallback(std::bind(&SudokuWindow::cb_click, this));
			    auto temp = tiles.at(row).back().get();
			    add(*temp); 
            }
            
        }

        // Legger til knapp for å sjekke brett
        check_button.setCallback(std::bind(&SudokuWindow::cb_check, this));
        victory_box.setVisible(false);
        add(check_button);
        add(victory_box);

}

// Returnerer tilen som inneholder spesifisert punkt i vinduet
std::shared_ptr<Tile>& SudokuWindow::get_tile(TDT4102::Point xy)  {
    return tiles[xy.y / tile_size][xy.x / tile_size];
}

// Velger en gitt tile, for å kunne endre tallet
void SudokuWindow::select_tile(std::shared_ptr<Tile>& tile) {
    if(tile->changeable) {
        if(selected_tile) {
            selected_tile->is_highlighted = false;
            selected_tile->update();
        }

        selected_tile = tile;
        selected_tile->is_highlighted = true;
        selected_tile->update();
    }
}

// Sjekker om et punkt er innenfor vinduet
bool SudokuWindow::in_range(TDT4102::Point xy) const { 
    return (xy.x >= 0 && xy.x< width && xy.y >= 0 && xy.y < height); 
}

// Kjører programmet. Tar inn et forhåndslagd brett fra en tekstfil
void SudokuWindow::run(std::string board_filename) {
    while(!should_close()) {

        if(won) {  
            toggle_visible(false);
            victory_box.setVisible(true);
            next_frame();
        }

        else {

            if(!game_started) {
                sudoku_board->load_board_from_file(board_filename);
                initialize_tiles();
                game_started = true;
            }
            draw_grid();
            handle_input();
            next_frame();
        }
    }
}

// Initialiserer det grafiske brettet. Henter forhåndsbestemte tall fra spillbrettet
void SudokuWindow::initialize_tiles() {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            int num = sudoku_board->get_cell(row, col);
            std::shared_ptr<Tile> tile = tiles.at(row).at(col);
            if(num) {
                tile->changeable = false; // Kan ikke endre på de forhåndsbestemte tallene
            }
            tile->set(num);
        }
    }
}

// Setter verdiene i spillbrettet basert på tallene i Tiles
void SudokuWindow::set_tiles() {
    int num;
    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            num = tiles.at(row).at(col)->number;
            sudoku_board->set_cell(row, col, num);
        }
    }
}

// Slår av eller på synligheten til brettet
void SudokuWindow::toggle_visible(bool visibility) {
    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            tiles.at(row).at(col)->setVisible(visibility);
        }
    }
}

// Tegner rutenett
void SudokuWindow::draw_grid() {
    int corr = 3; // Korreksjonsfaktor for å få nettet til å line up

    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            if (col % 3 == 0 && col != 0) {
                int x = pad_size + col * tile_size;
                draw_line({x + corr, pad_size}, {x+ corr, pad_size + board_height});
            }
        }
        if (row % 3 == 0 && row != 0) {
            int y = pad_size + row * tile_size;
            draw_line({pad_size, y + corr}, {pad_size + board_height, y + corr});
        }
    }
}

// Callback-funksjon for når brukeren klikker på en tile
void SudokuWindow::cb_click() {
	
    std::shared_ptr<Tile> tile;
	TDT4102::Point xy{this->get_mouse_coordinates()};
	if (!in_range(xy)) {
        std::cout << "Out of range!" << std::endl;
		return;
	}
	if (this->is_left_mouse_button_down()) {
		tile = get_tile(xy);
        select_tile(tile);
	}
}

// Sjekker om hele brettet er fyllt inn, og gyldig
void SudokuWindow::cb_check() {
    set_tiles();
    std::cout << "Board checked" << std::endl;
    if (sudoku_board->check_board() && sudoku_board->check_complete()) {
        std::cout << "You won!" << std::endl;
        won = true;
    }
}

// Sjekker for input fra tastaturet
void SudokuWindow::handle_input() {

    static bool last_0_state = false;
    static bool last_1_state = false;
    static bool last_2_state = false;
    static bool last_3_state = false;
    static bool last_4_state = false;
    static bool last_5_state = false;
    static bool last_6_state = false;
    static bool last_7_state = false;
    static bool last_8_state = false;
    static bool last_9_state = false;

    bool current_0_state = is_key_down(KeyboardKey::KEY_0);
    bool current_1_state = is_key_down(KeyboardKey::KEY_1);
    bool current_2_state = is_key_down(KeyboardKey::KEY_2);
    bool current_3_state = is_key_down(KeyboardKey::KEY_3);
    bool current_4_state = is_key_down(KeyboardKey::KEY_4);
    bool current_5_state = is_key_down(KeyboardKey::KEY_5);
    bool current_6_state = is_key_down(KeyboardKey::KEY_6);
    bool current_7_state = is_key_down(KeyboardKey::KEY_7);
    bool current_8_state = is_key_down(KeyboardKey::KEY_8);
    bool current_9_state = is_key_down(KeyboardKey::KEY_9);

    if (current_0_state && !last_0_state) { selected_tile->set(0); }
    if (current_1_state && !last_1_state) { selected_tile->set(1); }
    if (current_2_state && !last_2_state) { selected_tile->set(2); }
    if (current_3_state && !last_3_state) { selected_tile->set(3); }
    if (current_4_state && !last_4_state) { selected_tile->set(4); }
    if (current_5_state && !last_5_state) { selected_tile->set(5); }
    if (current_6_state && !last_6_state) { selected_tile->set(6); }
    if (current_7_state && !last_7_state) { selected_tile->set(7); }
    if (current_8_state && !last_8_state) { selected_tile->set(8); }
    if (current_9_state && !last_9_state) { selected_tile->set(9); }

}