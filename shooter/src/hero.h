//
// Created by Pun on 3/9/2019.
//

#include <ge211.h>

using Position = ge211:: Basic_position<float>;
using Dimensions = ge211:: Basic_dimensions<float>;
using Rectangle = ge211:: Basic_rectangle<float>;

#pragma once

class Hero{
public:

    float x;
    float y;
    float width;
    float height;

    int type;

    bool live;

    static Hero from_top_left(Position tl, Dimensions dims){
        return {tl.x, tl.y, dims.width, dims.height};
    }
    bool shooting;

    ge211::Position top_left() const
    {
        return {x,y+height};
    }


};
