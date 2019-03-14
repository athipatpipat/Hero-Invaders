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
//  - the state of the laser, including its location and velocity

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
    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// MEMBER FUNCTIONS
    ///

    void move_player_right();
    void move_player_left();

    void launch();

    void update();

    void update_hero();

    void hero_shoot();

    std::vector<Hero> heroes_;

    std::vector<Laser> hero_lasers;

    std::vector<Block> barriers_;

    void who_shoots();

    void addHero(Hero &hero) {
        heroes_.push_back(hero);
    }
    void addLaser(Laser &laser) {
        hero_lasers.push_back(laser);
    }


    ///
    /// MEMBER VARIABLES
    ///

    // position and dimensions of the lasers
    Laser               laser_;

    // the geometry parameters of the model
    Geometry const     geometry_;

    // if is true, game continues, if false, game ends
    bool               game_over;

    // amount of lives the player has in a game
    int                 player_lives;

    // position and dimensions of the player
    Block              player_;

    //direction that the heroes are moving.
    //true means right
    //false means left
    bool                hero_direction;

    // keeps track of the score of the game
    size_t              score;

    // velocity of the heroes
    float             hero_velocity;

    //used to determine the types of heroes
    size_t              counter;
};

