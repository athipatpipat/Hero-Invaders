#include "ui.h"
#include <string>
#include <iostream>

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
    ge211::Transform scale;
    scale.set_scale_x(sprite_scale_width);
    scale.set_scale_y(sprite_scale_height);
    //sprites.add_sprite(ball_sprite_, model_.ball_.top_left());
    sprites.add_sprite(laser_sprite_, model_.ball_.top_left().up_by(60).left_by(20));
   /* sprites.add_sprite(player_sprite_, model_.paddle_.top_left());*/
    ge211::Transform player_scale;
    player_scale.set_scale(thanos_scale);
    sprites.add_sprite(thanos_, model_.paddle_.top_left().up_by(75), 0, player_scale);
    auto str_score = std::to_string(model_.score);
    score_ = ge211::Text_sprite(str_score,ge211::Font("sans.ttf",20));

    sprites.add_sprite(score_,model_.geometry_.score_board);


    for(size_t i=0;i<model_.hero_lasers.size();i++){

      //  if(model_.heroes_[i].live){
            sprites.add_sprite(laser_sprite_, model_.hero_lasers[i].center_);
      //  }

    }



    for(Hero& hero:model_.heroes_ ){
        //make an if statement to check type of hero
        /*sprites.add_sprite(brick_sprite_, ge211::Position(hero.x,hero.y));*/
      if(hero.type == 1)
          sprites.add_sprite(batman_, ge211::Position(hero.x,hero.y), 0, scale);
      if(hero.type == 2)
          sprites.add_sprite(deadpool_, ge211::Position(hero.x,hero.y), 0, scale);
      if(hero.type == 3)
          sprites.add_sprite(turtle_, ge211::Position(hero.x,hero.y), 0, scale);
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

    ge211::Duration timepass(timer_.elapsed_time());

    if(timepass.seconds() > 0.5){
        std::cout<<"lap\n";
        model_.who_shoots();
        timer_.reset();
    }


    model_.update();
    model_.update_hero();
    model_.hero_shoot();

}





