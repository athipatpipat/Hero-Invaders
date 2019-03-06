//
// Created by Pun on 3/4/2019.
//

#pragma once

#include "geometry.h"
#include <ge211.h>

using Block = ge211::Rectangle;
struct Laser
{
    ///Constructor

    Laser(Block const& paddle, Geometry const&);


    ///Member Functions
    ge211::Position top_left() const;
    bool hits_top(Geometry const&) const;
    Laser next() const;
    bool hits_hero(Block const& block) const;
    bool destroy_hero(std::vector<Block>& heroes) const;


    ///Member Variables
    // The radius of the ball.
    int               radius_;

    // The velocity of the ball in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the ball.
    ge211::Position   center_;

    // Whether the ball is moving freely (true) or stuck to the top of the
    // paddle (false).
    bool              live_;

    ge211::Dimensions bullet_;

};

