//
// Created by Pun on 3/4/2019.
//

#include "laser.h"
#include "geometry.h"

static ge211::Position above_block(Block const& block,
                                   Geometry const& geometry)
{
    ge211::Position pos = block.top_left();
    pos = pos.right_by((.5)*(block.width));
    pos = pos.up_by(1 + geometry.ball_radius);
    return pos;
}

Laser::Laser(Block const& paddle, Geometry const& geometry)
        : radius_   (geometry.ball_radius)
        , velocity_ (geometry.ball_velocity0)
        , center_   (above_block(paddle, geometry))
        , live_     (false)
    {}


ge211::Position Laser::top_left() const
{
    ge211::Position pos = center_;

    pos = pos.up_by(radius_).left_by(radius_);
    return pos;
}


//Check if laser has hit top of the screen
bool Laser::hits_top(Geometry const&) const
{
    if((center_.y - radius_) < 0)
        return true;
    else
        return false;
}

//Make laser travel vertically
Laser Laser::next() const
{
    Laser result(*this);
    result.center_.y += result.velocity_.height;
    return result;
}


//Check if hero has been hit
bool Laser::hits_hero(Block const& block) const
{
    if((center_.x + radius_) < block.x || (block.x + block.width) < (center_.x - radius_) || (center_.y + radius_) < block.y || (block.y+block.height) < (center_.y - radius_))
        return false;
    else
        return true;
}

//Destroy hero that has been hit by laser
bool Laser::destroy_hero(std::vector<Block>& heroes) const
{
    for(ge211::Rectangle &brick : heroes ){
        if(hits_hero(brick)){
            std::swap(brick, heroes.back());
            heroes.pop_back();
            return true;
        }
    }
    return false;
}