#pragma once

#include <ge211.h>

struct Geometry
{
    ///Constructors
    Geometry() noexcept;


    ///Member Variables

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The dimensions of the player (the "villain" at the bottom):
    ge211::Dimensions player_dims_;

    // The number of pixels of space between each column and row of
    // heroes:
    ge211::Dimensions hero_spacing;

    // Dimension of laser
    ge211::Dimensions laser_dims_;

    // Number of columns of heroes:
    int hero_cols;

    // Number of rows of heroes:
    int hero_rows;

    // Number of pixels from top of screen to top of heroes formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of heroes formation:
    int side_margin;

    // Number of pixels from *top* of screen to *bottom* of heroes formation.
    int hero_depth;

    // Number of pixels from bottom of screen to bottom of paddle.
    int bottom_margin;


    int ball_radius;

    ge211::Position score_board;

    ge211::Dimensions laser_velocity0;

    // The initial position of the player. This is a member function because
    // it's computed from the other properties.
    ge211::Position paddle_top_left0() const noexcept;

    // The dimensions of each hero. Also computed from the other properties.

    ge211::Dimensions hero_dims() const noexcept;
};

