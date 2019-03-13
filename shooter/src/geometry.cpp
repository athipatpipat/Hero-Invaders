
#include "geometry.h"

// This is the default (and only) constructor for `Geometry`. It determines
// all the default values of all the member variables.
Geometry::Geometry() noexcept
        : hero_cols     {   5 }
        , hero_rows     {   5 }
        , top_margin     {  100 }
        , side_margin    {  170 }
        , hero_depth    {  300 }
        , bottom_margin  {   50 }
        , hero_spacing  {   10,   5 }
        , laser_velocity0 {    3, -10 }
        , laser_velocity_hero {3,5}
        , scene_dims     { 1024, 768 }
        , player_dims_   {  100,  20 }
        , ball_radius    {    5 }
        , laser_dims_ {5,15}
        , score_board {15,15}
        , barrier_top {600}
{ }

ge211::Position Geometry::paddle_top_left0() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - player_dims_.height };
}

// Computes how large each hero can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of heroes
// in that dimensions, and the number of space pixels to leave in between.

static int div_w_spacing(int total, int divisor, int space)
{
    if (divisor > 0)
        return (total - (divisor - 1) * space) / divisor;

    throw ge211::Client_logic_error("need at least 1 row & 1 column");
}

// Computes the dimensions of each hero from the other parameters.
Dimensions Geometry::hero_dims() const noexcept
{
    ge211::Dimensions field{scene_dims.width - 2 * side_margin,
                            hero_depth - top_margin};
    int width  = div_w_spacing(field.width, hero_cols, hero_spacing.width);
    int height = div_w_spacing(field.height, hero_rows, hero_spacing.height);
    return {width - 5 , height - 4};
}


