#include "Tile.h"

Tile::Tile(TDT4102::Point board_pos, TDT4102::Point pos, int size, int num) : 
Button(pos, 1.5*size, size, "") {

    if (num > 9 || num < 0) {
        throw(std::out_of_range("Number " + std::to_string(num) + " not between 0-9"));
    }
    this->number = num;
    this->is_highlighted = false;
    update();
}

// Oppdaterer grafikken til tilen. Sjekker om den er tom, om den er valgt, og om den kan endres
void Tile::update() {
    if(number) {
        setLabel(std::to_string(number));
    }
    else {
        setLabel("");
    }

    if(is_highlighted) {
        setButtonColor(highlight_color);
    }
    else {
        setButtonColor(default_color);
    }
    if(changeable) {
        setLabelColor(default_label_color);
    }
    else {
        setLabelColor(unchangeable_label_color);
    }

}

// Setter verdien på tilen til det gitte tallet
void Tile::set(int num) {
    if (num > 9 || num < 0) {
        throw(std::out_of_range("Number " + std::to_string(num) + " not between 0-9"));
    }
    number = num;
    update();
}