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
    //constructor for the heroes and barriers
    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// MEMBER FUNCTIONS
    ///
    // will be used to move player to the right when right arrow key is pressed
    void move_player_right();
    // will be used to move player to the right when left arrow key is pressed
    void move_player_left();
    // makes lasers shoot
    void launch();
    // updates the status of the player's laser
    void update();
    // updates the status of the heroes
    void update_hero();
    // makes the hero shoot
    void hero_shoot();
    // changes which hero shoots randomly
    void who_shoots();
    // adds heroes to the hero vector
    void addHero(Hero &hero) {
        heroes_.push_back(hero);
    }
    // adds lasers to the heroes' laser vector
    void addLaser(Laser &laser) {
        hero_lasers.push_back(laser);
    }


    ///
    /// MEMBER VARIABLES
    ///
    // vector for heroes
    std::vector<Hero> heroes_;
    // vector for heroes' lasers
    std::vector<Laser> hero_lasers;
    // vector for the barriers
    std::vector<Block> barriers_;

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

