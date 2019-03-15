#pragma once

#include <ge211.h>

using Position = ge211:: Basic_position<float>;
using Dimensions = ge211:: Basic_dimensions<float>;


struct Geometry
{
    ///Constructors
    Geometry() noexcept;

    ///Member Variables
    //Dimension of barrier
    ge211::Dimensions barrier_dims;

    //Dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The dimensions of the player
    ge211::Dimensions player_dims_;

    // The number of pixels of space between each column and row of heroes
    ge211::Dimensions hero_spacing;

    //Center of the screen
    ge211::Position center;

    //Dimension of laser
    ge211::Dimensions laser_dims_;

    // Number of columns of heroes
    int hero_cols;

    // Number of rows of heroes
    int hero_rows;

    // Number of pixels from top of screen to top of heroes formation
    int top_margin;

    // Number of pixels from sides of screen to sides of heroes formation
    int side_margin;

    // Number of pixels from top of screen to bottom of heroes formation
    int hero_depth;

    // Number of pixels from bottom of screen to bottom of player
    int bottom_margin;

    // Number of pixel from top of screen to top of barrier
    int barrier_top;

    // Position of player's score
    ge211::Position score_board;

    // Position of player's live count
    ge211::Position live_count;

    // Velocity of player's laser
    ge211::Dimensions laser_velocity0;

    // Velocity of hero's laser
    ge211::Dimensions laser_velocity_hero;

    // The initial position of the player. This value is computed from other member variables
    ge211::Position player_top_left0() const noexcept;

    //The dimensions of each hero. Also computed from the other member variables
    Dimensions hero_dims() const noexcept;
};

