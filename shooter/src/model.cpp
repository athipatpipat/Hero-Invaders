#include "model.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , hero_direction(true)
        , score(0)
        , player_(Block::from_top_left(geometry_.player_top_left0(),
                                       geometry_.player_dims_))
        , laser_(player_, geometry_)
        , counter(0)
        , hero_velocity(1)
        , game_over(false)
        , player_lives(3)

{
    std::srand(std::time(0));
    for(size_t j = 0; j < geometry_.hero_rows; j++){

        for(size_t i = 0; i < geometry_.hero_cols; i++){
            Hero hero;

            int x = (i * (geometry_.hero_spacing.width + geometry_.hero_dims().width));
            int y = (j * (geometry_.hero_spacing.height + geometry_.hero_dims().height));
            hero = Hero::from_top_left({(geometry_.side_margin + x), (geometry_.top_margin + y)}, geometry_.hero_dims());
            Laser laser(hero,geometry_);

            switch(counter){
                case 0: hero.type = 1;
                break;
                case 1:
                case 2: hero.type = 2;
                break;
                case 3:
                case 4: hero.type = 3;
                break;
            }
            bool TrueFalse = (std::rand() % 100) < 10;

            hero.shooting = TrueFalse;

            if(hero.shooting){
                laser.live_ = true;
            }else{
                laser.live_ = false;
            }

            hero.live = true;
            addHero(hero);
            addLaser(laser);
        }
        counter++;
    }

    for(size_t k = 0; k < 4; k++) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                Block barrier;
                barrier = Block::from_top_left({75 + (j * 33) + (k * geometry_.scene_dims.width/4), 500 + i * 33}, geometry_.barrier_dims);
                barriers_.push_back(barrier);
            }
        }
    }
}

void Model::launch()
{
    laser_.live_ = true;
}

void Model::move_player_right(){
    player_.x += 20;
    if(!laser_.live_)
        laser_.center_.x += 20;
}

void Model::move_player_left() {
    player_.x -= 20;
    if(!laser_.live_)
        laser_.center_.x -= 20;
}

void Model::update(){
    if(!laser_.live_)
        return;
    else{
        Laser newlaser = laser_.next();

        if(newlaser.hits_top(geometry_)) {
            laser_ = Laser(player_, geometry_);
            return;
        }
        if(newlaser.destroy_hero(heroes_,score, hero_velocity)) {
            laser_ = Laser(player_, geometry_);
            return;
        }
        if(newlaser.destroy_barrier(barriers_)){
            laser_ = Laser(player_, geometry_);
            return;
        }
        laser_ = laser_.next();
    }
}

void Model::update_hero(){
    if(hero_direction){
        for (size_t i = 0; i < hero_lasers.size(); i++) {
            heroes_[i].x += hero_velocity;
            if(!hero_lasers[i].live_){
                hero_lasers[i].center_.x += hero_velocity;
            }
        }
    }

    if(!hero_direction){
        for (size_t i = 0; i < hero_lasers.size(); i++) {
            heroes_[i].x -= hero_velocity;
            
            if(!hero_lasers[i].live_){
                hero_lasers[i].center_.x -= hero_velocity;
            }
        }
    }

    //check if any hero have gone past right side
    for(Hero& hero:heroes_){
        if(hero.x + hero.width > geometry_.scene_dims.width){
            hero_direction = false;
            for (size_t i = 0; i < hero_lasers.size(); i++) {
                heroes_[i].y += 3;

                if(!hero_lasers[i].live_){
                    hero_lasers[i].center_.y += 3;
                }

            }
        }
        if(hero.x < 0){
            hero_direction = true;
            for (size_t i = 0; i < hero_lasers.size(); i++) {
                heroes_[i].y += 3;

                if(!hero_lasers[i].live_){
                    hero_lasers[i].center_.y += 3;
                }
            }
        }
    }

    //check if hero has hit barrier line, if hit, make game_over == true, go to UI and stop updating everything

    for(Hero& hero:heroes_){
        if((hero.y + hero.height/2)>geometry_.barrier_top ){
            game_over = true;
        }
    }
}

void Model::who_shoots(){
    std::srand(std::time(0));
    for (size_t i = 0; i < hero_lasers.size(); i++) {
        if(heroes_[i].live){
            bool TrueFalse = (std::rand() % 100) < 6;
            heroes_[i].shooting = TrueFalse;
            if(heroes_[i].shooting){
                hero_lasers[i].live_ = true;
            }

        }
    }
}

void Model::hero_shoot() {
    for (size_t i = 0; i < hero_lasers.size(); i++) {
        if(!hero_lasers[i].live_){
            continue;
        }
        //if hero can shoot, but laser is not live, this check doesn't stop it from moving the laser
        if ((!heroes_[i].live && !heroes_[i].shooting)) {
            if (hero_lasers[i].live_) {
            }
            else {
                continue;
            }
        }
        Laser new_laser = hero_lasers[i].next();

        if (new_laser.hits_bottom(geometry_)) {
            hero_lasers[i].live_ = false;

            if (heroes_[i].live && heroes_[i].shooting) {
                hero_lasers[i] = Laser(heroes_[i],geometry_);
                hero_lasers[i].live_ = true;

            }
            return;
        }

        if (new_laser.destroy_barrier(barriers_)){
            hero_lasers[i] = Laser(heroes_[i],geometry_);
            hero_lasers[i].live_ = true;
            return;
        }
        if (new_laser.destroy_player(player_)) {
            hero_lasers[i] = Laser(heroes_[i], geometry_);
            hero_lasers[i].live_ = true;
            player_lives--;
            if(player_lives == 0){
                game_over = true;
            }
            return;
        }

        hero_lasers[i] = hero_lasers[i].next();
    }

}





