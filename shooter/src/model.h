// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - the game geometry (the sizes of things such as the heroes, the player,
//    and the screen)
//
//  - the locations and sizes of all the heroes
//
//  - the location and size of the player
//
//  - the state of the laser, including its location and velocity (

#pragma once


#include "geometry.h"
#include <vector>
#include "laser.h"







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

    // Makes the laser live.
    void launch();


    void update();

    //Moves hero
    void update_hero();

    void hero_shoot();

    std::vector<Hero> heroes_;

    std::vector<Laser> hero_lasers;

    std::vector<Block> barriers_;

    bool no_lasers();

    void who_shoots();

    void addHero(Hero &hero) {
        heroes_.push_back(hero);
    }
    void addLaser(Laser &laser) {
        hero_lasers.push_back(laser);
    }

   // void switch_shooter();




    ///
    /// MEMBER VARIABLES
    ///

    Laser               ball_;
    Geometry const     geometry_;


    bool               game_over;

    int                 player_lives;

    Block              paddle_;

    //direction that the heroes are moving.
    //true means right
    //false means left
    bool                hero_direction;

    size_t              score;

    float             hero_velocity;

    size_t              counter;

  //  ge211::Timer        timer_;
};

