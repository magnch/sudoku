#pragma once
#include <iostream>
#include "AnimationWindow.h"
#include "widgets/Button.h"

const TDT4102::Color default_color = TDT4102::Color::white;
const TDT4102::Color highlight_color = TDT4102::Color::sky_blue;
const TDT4102::Color default_label_color = TDT4102::Color::dim_grey;
const TDT4102::Color unchangeable_label_color = TDT4102::Color::black;

struct Tile : public TDT4102::Button{
    
    Tile(TDT4102::Point board_pos, TDT4102::Point pos, int size, int number = 0);

    int number;
    bool is_highlighted;
    bool changeable = true;
    TDT4102::Point board_pos;
    
    void set(int num);
    void update();

};