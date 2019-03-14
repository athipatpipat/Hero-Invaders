//
// Created by Pun on 3/4/2019.
//

#pragma once

#include "geometry.h"
#include "hero.h"
#include <ge211.h>

using Position = ge211:: Basic_position<float>;
using Dimensions = ge211:: Basic_dimensions<float>;
using Rectangle = ge211:: Basic_rectangle<float>;

using Block = ge211::Rectangle;



struct Laser
{
    ///Constructor

    Laser(Block const& paddle, Geometry const&);
    Laser(Hero const& hero, Geometry const&);


    ///Member Functions
    ge211::Position top_left() const;
    bool hits_top(Geometry const&) const;
    bool hits_bottom(Geometry const& geometry) const;

    Laser next() const;
    bool hits_hero(Hero const& block) const;
    bool destroy_hero(std::vector<Hero>& heroes, size_t & score, float& velocity) const;

    bool hits_player(Block const& paddle) const;
    bool destroy_player(Block& paddle) const;

    bool hero_hits_barrier(Block const& brick) const;
    bool hits_barrier(Block const& brick) const;
    bool destroy_barrier(std::vector<Block>& barrier);


    ///Member Variables

    // The velocity of the laser in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the ball.
    ge211::Position   center_;

    // Whether the laser is moving freely (true) or has not been shot yet (false).
    bool              live_;

    ge211::Dimensions bullet_;


};

