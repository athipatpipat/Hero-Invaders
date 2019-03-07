#include "ui.h"


ge211::Color const paddle_color  {255, 255, 127};
ge211::Color const brick_color   {100, 100, 100};
ge211::Color const ball_color    {255, 127, 127};

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Ui::Ui(Model& model)
        : model_(model)
{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites)
{
    //sprites.add_sprite(ball_sprite_, model_.ball_.top_left());
    sprites.add_sprite(laser_sprite_, model_.ball_.top_left());
    sprites.add_sprite(player_sprite_, model_.paddle_.top_left());

    for(Block brick:model_.heroes_ ){

        sprites.add_sprite(brick_sprite_, ge211::Position(brick.x,brick.y));
    }
}


void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::left()){
        model_.move_player_left();
    } else if(key == ge211::Key::right()){
        model_.move_player_right();
    } else if (key == ge211::Key::code(' ')) {
        model_.launch();
    }

}

void Ui::on_frame(double)
{
    model_.update();
    model_.update_hero();
}





