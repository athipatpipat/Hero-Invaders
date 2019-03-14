//
// Created by Pun on 3/4/2019.
//

#include "laser.h"
#include "geometry.h"

#include <iostream>

// Positions laser above player
static ge211::Position above_block(Block const& block,
                                   Geometry const& geometry)
{
    ge211::Position pos = block.top_left();
    pos = pos.right_by((.5)*(block.width));
    pos = pos.up_by(1 + geometry.laser_dims_.height/2);
    return pos;
}

// Positions laser below each hero
static ge211::Position below_block(Hero const& hero,
                                   Geometry const& geometry)
{
    ge211::Position pos = hero.top_left();
    pos = pos.right_by((.5)*(hero.width));
    pos = pos.up_by(1 + geometry.laser_dims_.height/2);
    return pos;
}

// Constructor for player's laser
Laser::Laser(Block const& player, Geometry const& geometry)
        : bullet_   (geometry.laser_dims_)
        , velocity_ (geometry.laser_velocity0)
        , center_   (above_block(player, geometry).x, above_block(player, geometry).y )
        , live_     (false)
{}

// Constructor for heroes' lasers
Laser::Laser(Hero const& hero, Geometry const& geometry)
        : bullet_   (geometry.laser_dims_)
        , velocity_ (geometry.laser_velocity_hero)
        , center_   (below_block(hero, geometry).x, below_block(hero, geometry).y)
        , live_     (false)
{}

// Returns position of top left of lasers
ge211::Position Laser::top_left() const //since we are using this to draw, we must change this as position of player changes
{
    ge211::Position pos = {static_cast<int>(center_.x),static_cast<int>(center_.y)};

    pos = pos.up_by(bullet_.height/2).left_by(bullet_.width/2);
    return pos;
}


// Checks if laser has hit top of the screen
bool Laser::hits_top(Geometry const&) const
{
    if((center_.y - bullet_.height/2 - 60) < 0)
        return true;
    else
        return false;
}

// Checks if laser has hit bottom of the screen
bool Laser::hits_bottom(Geometry const& geometry) const
{
    return ((center_.y + bullet_.height/2) > geometry.scene_dims.height);
}


//Make laser travel vertically
Laser Laser::next() const
{
    Laser result(*this);
    result.center_.y += result.velocity_.height;
    return result;
}

// Checks if the player's laser has hit a hero
bool Laser::hits_hero(Hero const& block) const
{
    if((center_.x + bullet_.width/2) < block.x || (block.x + block.width) < (center_.x - bullet_.width/2) || (center_.y +  bullet_.height/2 - 60) < block.y || (block.y+block.height) < (center_.y - bullet_.height/2 - 60)) {
        return false;
    }
    else
        return true;
}

//Destroy hero that has been hit by laser
bool Laser::destroy_hero(std::vector<Hero>& heroes, size_t& score, float& velocity) const
{
    for(Hero &hero : heroes ){
        if(hits_hero(hero)){
            velocity += 0.05;
            switch(hero.type){
                case 1: score += 30;
                break;
                case 2: score += 20;
                break;
                case 3: score += 10;
                break;
            }
            hero.live = false;
            hero.shooting = false;
            std::swap(hero, heroes.back());

            heroes.pop_back();
            return true;
        }
    }
    return false;
}

// checks if one of the heroes' lasers has hit the player
bool Laser::hits_player(Block const& player) const
{
    if((center_.x + bullet_.width/2 ) < player.x || (player.x + player.width) < (center_.x - bullet_.width/2) || (center_.y +  bullet_.height/2) < player.y || (player.y+player.height) < (center_.y - bullet_.height/2))
        return false;
    else
        return true;
}

// will be used to destroy player if player lives is 0
bool Laser::destroy_player(Block& player) const
{
    if(hits_player(player)){
    }
}

// checks if the player's laser has hit a barrier
bool Laser::hits_barrier(Block const& brick) const {
    if ((center_.x + bullet_.width / 2) < brick.x ||
        (brick.x + brick.width) < (center_.x - bullet_.width / 2 ) ||
        (center_.y + (bullet_.height /2) - 60) < brick.y ||
        (brick.y + brick.height) < (center_.y - (bullet_.height/2) - 60))
        return false;
    else
        return true;
}

// checks if the heroes' lasers has hit a barrier
bool Laser::hero_hits_barrier(Block const& brick) const {
    if ((center_.x + bullet_.width / 2) < brick.x ||
        (brick.x + brick.width) < (center_.x - bullet_.width / 2) ||
        (center_.y + bullet_.height / 2) < brick.y ||
        (brick.y + brick.height) < (center_.y - bullet_.height / 2 ))
        return false;
    else
        return true;
}

// gets rid of a barrier when hit by either player or hero
bool Laser::destroy_barrier(std::vector<Block>& barriers)
{
    for(Block &barrier : barriers){
        if(hits_barrier(barrier) || hero_hits_barrier(barrier)){
            std::swap(barrier, barriers.back());
            barriers.pop_back();
            return true;
        }
    }
    return false;
}
