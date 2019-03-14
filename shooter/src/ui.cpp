#include "ui.h"
#include <string>
#include <iostream>

ge211::Color const paddle_color  {255, 255, 127};
ge211::Color const ball_color    {255, 127, 127};
ge211::Color const barrier_color {105, 105, 105};

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

void Ui::draw(ge211::Sprite_set& sprites) {
    ge211::Transform scale;
    scale.set_scale_x(sprite_scale_width);
    scale.set_scale_y(sprite_scale_height);
    //sprites.add_sprite(ball_sprite_, model_.ball_.top_left());

    //sprites.add_sprite(player_sprite_, model_.paddle_.top_left());*/
    ge211::Transform player_scale;
    player_scale.set_scale(thanos_scale);

    auto str_score = std::to_string(model_.score);
    score_ = ge211::Text_sprite("Score: " + str_score, ge211::Font("sans.ttf", 20));

    auto str_live = std::to_string(model_.player_lives);
    lives_ = ge211::Text_sprite("Lives: " + str_live, ge211::Font("sans.ttf", 20));


    if (!model_.game_over) {
        sprites.add_sprite(laser_sprite_, model_.ball_.top_left().up_by(60));
        sprites.add_sprite(player_sprite_, model_.paddle_.top_left());
        sprites.add_sprite(thanos_, model_.paddle_.top_left().up_by(75), 0, player_scale);
        sprites.add_sprite(score_, model_.geometry_.score_board);
        sprites.add_sprite(lives_, model_.geometry_.live_count);


        for (size_t i = 0; i < model_.hero_lasers.size(); i++) {
         if (model_.hero_lasers[i].live_) {
                sprites.add_sprite(laser_sprite_, model_.hero_lasers[i].center_);
         }
        }

        for(Block barrier:model_.barriers_){
            sprites.add_sprite(barrier_sprite_, ge211::Position(barrier.x, barrier.y));
        }

        for (Hero &hero:model_.heroes_) {
            //make an if statement to check type of hero
            /*sprites.add_sprite(brick_sprite_, ge211::Position(hero.x,hero.y));*/
            if (hero.type == 1)
                sprites.add_sprite(batman_, ge211::Position(hero.x, hero.y), 0, scale);
            if (hero.type == 2)
                sprites.add_sprite(deadpool_, ge211::Position(hero.x, hero.y), 0, scale);
            if (hero.type == 3)
                sprites.add_sprite(turtle_, ge211::Position(hero.x, hero.y), 0, scale);
        }
    }
    else{
        game_over_msg = ge211::Text_sprite("Game Over", ge211::Font("sans.ttf", 20));
        sprites.add_sprite(game_over_msg,model_.geometry_.center);

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

void Ui::on_frame(double) {

   if(!model_.game_over) {

        /*
        ge211::Duration timepass(timer_.elapsed_time());

        if (timepass.seconds() > 4) {
            model_.who_shoots();
            timer_.reset();
        }
         */
        model_.who_shoots();
        model_.update();
        model_.update_hero();
        model_.hero_shoot();
    }

}





