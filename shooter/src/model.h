
//
// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - the game geometry (the sizes of things such as bricks, the paddle,
//    and the screen),
//
//  - the locations and sizes of all the bricks,
//
//  - the location and size of the paddle (the thing at the bottom that you
//    control), and
//
//  - the state of the ball, including its location and velocity (grouped in
//    the `Ball` struct).
//
// It also provides three member functions to help the UI in updating it.
//

#pragma once


#include "geometry.h"
#include <vector>
#include "laser.h"

using Block = ge211::Rectangle;
// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from its geometry.
    //
    // The `= Geometry()` syntax makes the argument optional, in which case
    // it defaults to the default `Geometry`. That is, you can explicitly
    // create a `Geometry` to pass the `Model` constructor like so:
    //
    //     Geometry geo;
    //     geo.ball_radius = 2;
    //     Model model(geo);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Geometry` (as defined in geometry.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Geometry`s into `Model`s if needed. You don't want that.
    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// MEMBER FUNCTIONS
    ///

    void move_player_right();
    void move_player_left();

    // Makes the ball live.
    void launch();

    // Changes the x coordinate of the (left edge of the) paddle to the
    // given x. Then, only if the ball is dead, updates the ball to
    // follow the paddle.
    void paddle_to(int x);

    // Updates the state of the game for one frame (usually 1/60 s).
    //
    // If the ball is dead then nothing happens. Otherwise there are
    // several possible cases, depending on the speculative next
    // position of the ball according to `Ball::next() const`. In
    // particular:
    //
    //  1. If the next position of the ball is off the bottom of the
    //     screen (according to Ball::hits_bottom(Geometry const&)),
    //     resets the ball to dead and returns.
    //
    //  2. If the next position of the ball would be off the top of
    //     the screen, reflects the velocity of the ball vertically.
    //
    //  3. If the next position of the ball would be off one side of
    //     the screen, reflects the velocity of the ball horizontally.
    //
    // (Note that cases 2 and 3 can both happen at the same time!)
    //
    //  4. If the next position of the ball destroys a brick (using
    //     Ball::destroy_bricks(std::vector<Block>&)) then it reflects
    //     the velocity of the ball both horizontally and vertically [1].
    //
    //  5. If the next position of the ball hits the block then it
    //     reflects vertical component of the ball's velocity and
    //     adds `boost` to the horizontal component [2].
    //
    // In all cases where the ball is still live (2–5), we then update
    // the ball to its next position for real.
    //
    // [1] Yes, this is weird physics.
    //
    // [2] This causes the effect where the velocity of the ball varies
    //     after each bounce off the paddle. While this adjustment is
    //     random, we require the UI component to perform the actual
    //     random number generation and pass the result to the model.
    //     This makes the model deterministic and thus easier to test.
    //
    void update();

    //Moves hero
    void update_hero();

    ///
    /// MEMBER VARIABLES
    ///

    // The geometry parameters of the model. See geometry.h for a
    // description of what this determines. Models can be constructed
    // with different geometries, but the geometry never changes on an
    // existing model.
    Geometry const     geometry_;

    // All of the bricks, in no particular order. `Block` is a type
    // alias for `ge211::Rectangle`, which means it gives both the
    // position of the top-left corner of each brick and the dimensions.
    std::vector<Block> heroes_;

    // The position and dimensions of the paddle.
    Block              paddle_;

    //direction that the heroes are moving.
    //true means right
    //false means left
    bool                hero_direction;

    size_t              score;

    Laser               ball_;
};

