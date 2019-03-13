#include "model.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , hero_direction(true)
        , score(0)
        , paddle_(Block::from_top_left(geometry_.paddle_top_left0(),
                                       geometry_.player_dims_))
        , ball_(paddle_, geometry_)
        , counter(0)
        , hero_velocity(3)

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
            bool TrueFalse = (std::rand() % 100) < 30;
            if(TrueFalse){
                std::cout << "True\n";
            }else{
                std::cout << "False\n";
            }
            hero.shooting = TrueFalse;
            hero.live = true;
            addHero(hero);
            addLaser(laser);
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
        if(newball.destroy_hero(heroes_,score, hero_velocity)) {
            ball_ = Laser(paddle_, geometry_);
            return;
        }

        ball_ = ball_.next();
    }

}

void Model::update_hero(){

    if(hero_direction){
        for(Hero& hero:heroes_ ){
            hero.x += hero_velocity;
        }
    }

    if(!hero_direction){
        for(Hero& hero:heroes_ ){
            hero.x -= hero_velocity;
        }
    }

    //check if any hero have gone past right side
    for(Hero& hero:heroes_){
        if(hero.x + hero.width > geometry_.scene_dims.width){
            hero_direction = false;
            for(Hero& hero:heroes_){
                hero.y += 3;
            }
        }
        if(hero.x < 0){
            hero_direction = true;
            for(Hero& hero:heroes_){
                hero.y += 3;
            }
        }
    }
}



void Model::who_shoots(){
    std::srand(std::time(0));
      //TrueFalse;
      /*
    if(TrueFalse){
        std::cout << "True\n";
    }else{
        std::cout << "False\n";
    }
       */
    for(Hero& hero:heroes_){
        if(hero.live){
            bool TrueFalse = (std::rand() % 100) < 30;
            hero.shooting = TrueFalse;
        }
    }
}

/*
void Model::switch_shooter(){
    ge211::Duration dur(3);
    if(timer_.elapsed_time() == dur){
        who_shoots();
    }
    timer_.reset();
}
 */

//need a function to call who_shoots when all lasers are dead

void Model::hero_shoot() {
    for (size_t i = 0; i < hero_lasers.size(); i++) {

        /*
        if(!heroes_[i].shooting){
            return;
        }
         */



        //if hero.shooting has been set to false but laser still in flight, continue moving the laser
        if ((!heroes_[i].live || !heroes_[i].shooting) &&
            (hero_lasers[i].live_)) { //if hero dies but laser still in flight or if hero cannot shoot anymore
            if (hero_lasers[i].live_) { //continue if laser still alive
            } else {
                //std::cout<< "laser dies\n";
                continue; //if hero dies, or cant shoot, return
            }
        }

        //hero cannot shoot more if their laser is still alive
        //need to make hero unable to shoot until all laser have been cleared
        //if(!hero_lasers[i].live_)
        //   return;
        //  else{

        if (heroes_[i].shooting) {

            Laser new_laser = hero_lasers[i].next();

            if (new_laser.hits_bottom(geometry_)) {
                hero_lasers[i].live_ = false;

                //have a timer and switch every shooters every time timer hits certain time

                if (heroes_[i].live &&
                    heroes_[i].shooting) { //if the laser reaches the end, and hero is still alive, reset the laser, if not, kill laser
                    hero_lasers[i] = Laser(heroes_[i],
                                           geometry_); //if laser reaches the end, and hero is shooting, make new laser (does not make sense)
                }
                return;
            }


            if (new_laser.destroy_player(paddle_)) {
                hero_lasers[i] = Laser(heroes_[i], geometry_);
                return;
            }

            hero_lasers[i] = hero_lasers[i].next();
            //  }
        }

    }


}





