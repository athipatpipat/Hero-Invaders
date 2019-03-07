#include "model.h"
#include <iostream>



Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , hero_direction(true)
        , score(0)
        , paddle_(Block::from_top_left(geometry_.paddle_top_left0(),
                                       geometry_.player_dims_))
        , ball_(paddle_, geometry_)

{
    /*
    for(size_t i = 0; i < geometry_.hero_cols; i++){
        for(size_t j = 0; j < geometry_.hero_rows; j++){
            Block hero;
            size_t x = (i * (geometry_.hero_spacing.width + geometry_.hero_dims().width));
            size_t y = (j * (geometry_.hero_spacing.height + geometry_.hero_dims().height));
            hero= Block::from_top_left({(geometry_.side_margin + x), (geometry_.top_margin + y)}, geometry_.hero_dims());
            heroes_.push_back(hero);
            //change hero type here
        }
    }
    */

    for(size_t j = 0; j < geometry_.hero_rows; j++){
        int counter = 0;
        for(size_t i = 0; i < geometry_.hero_cols; i++){
            Hero hero;


            int x = (i * (geometry_.hero_spacing.width + geometry_.hero_dims().width));
            int y = (j * (geometry_.hero_spacing.height + geometry_.hero_dims().height));
            hero = Hero::from_top_left({(geometry_.side_margin + x), (geometry_.top_margin + y)}, geometry_.hero_dims());
            switch(counter){
                case 0: hero.type = 1;
                case 1:
                case 2: hero.type = 2;
                case 3:
                case 4: hero.type = 3;
            }
            heroes_.push_back(hero);
            //change hero type here
        }
        counter++;
    }
}



void Model::launch()
{
    ball_.live_ = true;
}

void Model::move_player_right(){
    paddle_.x += 10;
    if(!ball_.live_)
        ball_.center_.x += 10;
}

void Model::move_player_left() {
    paddle_.x -= 10;
    if(!ball_.live_)
        ball_.center_.x -= 10;
}


void Model::update(){

    if(!ball_.live_)
        return;
    else{
        Laser newball = ball_.next();
        if(newball.hits_top(geometry_)) {
            ball_ = Laser(paddle_, geometry_);
            return;
        }
        if(newball.destroy_hero(heroes_)) {
            //have an if statement to check which type of hero has been destroyed to allocated correct points
            score += 10;
            ball_ = Laser(paddle_, geometry_);
            return;
        }

        ball_ = ball_.next();
    }

}

void Model::update_hero(){

    if(hero_direction){
        for(Block& hero:heroes_ ){
            hero.x += 2;
        }
    }

    if(!hero_direction){
        for(Block& hero:heroes_ ){
            hero.x -= 2;
        }
    }

    //check if any hero have gone past right side
    for(Block& hero:heroes_){
        if(hero.x + hero.width > geometry_.scene_dims.width){
            hero_direction = false;
            for(Block& hero:heroes_){
                hero.y += 3;
            }
        }
        if(hero.x < 0){
            hero_direction = true;
            for(Block& hero:heroes_){
                hero.y += 3;
            }
        }
    }
}








