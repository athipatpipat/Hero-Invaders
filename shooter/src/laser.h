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
    // Constructor for player's laser
    Laser(Block const& player, Geometry const&);
    // Constructor for heroes' lasers
    Laser(Hero const& hero, Geometry const&);


    ///Member Functions
    // Returns position of top left of lasers
    ge211::Position top_left() const;
    // Checks if laser has hit top of the screen
    bool hits_top(Geometry const&) const;
    // Checks if laser has hit bottom of the screen
    bool hits_bottom(Geometry const& geometry) const;
    //Make laser travel vertically
    Laser next() const;
    // Checks if the player's laser has hit a hero
    bool hits_hero(Hero const& block) const;
    //Destroy hero that has been hit by laser
    bool destroy_hero(std::vector<Hero>& heroes, size_t & score, float& velocity) const;
    // checks if one of the heroes' lasers has hit the player
    bool hits_player(Block const& player) const;
    // will be used to destroy player if player lives is 0
    bool destroy_player(Block& player) const;
    // checks if the player's laser has hit a barrier
    bool hero_hits_barrier(Block const& brick) const;
    // checks if the heroes' lasers has hit a barrier
    bool hits_barrier(Block const& brick) const;
    // gets rid of a barrier when hit by either player or hero
    bool destroy_barrier(std::vector<Block>& barrier);

    ///Member Variables

    // The velocity of the laser in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the ball.
    Position          center_;

    // Whether the laser is moving freely (true) or has not been shot yet (false).
    bool              live_;

    // The dimensions of the laser
    ge211::Dimensions bullet_;
};

