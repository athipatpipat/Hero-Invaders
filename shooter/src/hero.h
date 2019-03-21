//
// Created by Pun on 3/9/2019.
//

#pragma once

#include <ge211.h>

using Position = ge211:: Basic_position<float>;
using Dimensions = ge211:: Basic_dimensions<float>;
using Rectangle = ge211:: Basic_rectangle<float>;

class Hero{
public:

    //Constructor that gives position and dimension to the hero
    static Hero from_top_left(Position tl, Dimensions dims){
        return {tl.x, tl.y, dims.width, dims.height};
    }

    //Top left position of hero
    ge211::Position top_left() const
    {
        return {static_cast<int>(x),static_cast<int>(y+height)};
    }

    //X coordinate of hero's center
    float x;

    //Y coordinate of hero's center
    float y;

    //Width of hero's hitbox
    float width;

    //Width of hero's hitbox
    float height;
    
    //Type of hero which determines amount of pointers player gets by killing it
    int type;

    //False if hero has been hit by player's laser
    bool live;

    //True if hero can shoot
    bool shooting;


};
