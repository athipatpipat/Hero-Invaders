#include "model.h"
#include <catch.h>
#include <math.h>


//Check that the horizontal velocity of all alive heroes are increased when a hero has been killed
TEST_CASE("Hero moves faster when one hero dies"){
    Geometry geometry;
    Model m(geometry);
    Hero hero1;
    hero1.x = 300;
    hero1.y = 300;
    hero1.width = 50;
    hero1.height = 50;
    hero1.live = true;
    m.heroes_.push_back(hero1);
    CHECK(m.hero_velocity == 1);

    m.laser_.center_.x = 300;
    m.laser_.center_.y = 360;
    m.launch();

    CHECK(m.laser_.hits_hero(hero1));
    m.laser_.destroy_hero(m.heroes_, m.score, m.hero_velocity);
    m.update();

    //Check that velocity has been increased from 1 to 1.1 after one hero was killed
    CHECK(std::fabs(m.hero_velocity - 1.1) < std::numeric_limits<float>::epsilon());

}

//Check that player's lives is decreased by 1 when player gets hit by a hero's laser
TEST_CASE("Player loses one life when hit"){
    Geometry geometry;
    Model m(geometry);

    m.player_.x = 50;
    m.player_.y = 55;

    CHECK(m.player_lives == 3);

    Hero hero1;
    hero1.type = 1;
    hero1.x = 50;
    hero1.y = 55;
    m.heroes_.push_back(hero1);

    Laser laser(hero1, geometry);
    laser.live_ = true;
    laser.center_.x = 50;
    laser.center_.y = 55;
    m.hero_lasers.push_back(laser);
    m.hero_shoot();

    CHECK(m.player_lives == 2);

}

//Check that game_over is set to true when player's lives is 0
TEST_CASE("Game Over message when life is zero"){
    Geometry geometry;
    Model m(geometry);
    m.player_lives = 3;
    CHECK_FALSE(m.game_over);
    m.player_lives = 0;
    m.update();
    CHECK(m.game_over);
}

//Check that player's score increase by different amount depending on which type of hero has been killed
TEST_CASE("Different types of hero give different points when killed "){
    Geometry geometry;
    Model m(geometry);

    m.laser_.center_.x = 300;
    m.laser_.center_.y = 360;
    m.launch();

    Hero hero1;
    hero1.type = 1;
    hero1.x = 300;
    hero1.y = 300;
    hero1.width = 50;
    hero1.height = 50;
    hero1.live = true;

    Hero hero2;
    hero2.type = 2;
    hero2.x = 300;
    hero2.y = 300;
    hero2.width = 50;
    hero2.height = 50;
    hero2.live = true;

    Hero hero3;
    hero3.type = 3;
    hero3.x = 300;
    hero3.y = 300;
    hero3.width = 50;
    hero3.height = 50;
    hero3.live = true;


    m.heroes_.push_back(hero1);

    m.laser_.destroy_hero(m.heroes_,m.score,m.hero_velocity);
    CHECK(m.laser_.hits_hero(hero1));
    CHECK(m.score==30);

    m.heroes_.push_back(hero2);
    m.laser_.destroy_hero(m.heroes_,m.score,m.hero_velocity);
    CHECK(m.score==50);

    m.heroes_.push_back(hero3);
    m.laser_.destroy_hero(m.heroes_,m.score,m.hero_velocity);
    CHECK(m.score==60);
    
}

//Barrier gets smaller when it is hit by laser
TEST_CASE("Barrier dies when hit by laser"){
    Geometry geometry;
    Model m(geometry);

    m.laser_.center_.x = 300;
    m.laser_.center_.y = 360;
    m.launch();
    m.barriers_.clear();
    Block barrier1;
    barrier1.x = 300;
    barrier1.y = 300;
    m.barriers_.push_back(barrier1);
    CHECK(m.barriers_.size() == 1);
    CHECK(m.laser_.destroy_barrier(m.barriers_));
    m.update();
    CHECK(m.barriers_.size() == 0);
}

TEST_CASE("Player's laser resets when hits top"){
    Geometry geometry;
    Model m(geometry);

    m.laser_.live_ = true;
    m.laser_.center_.x = 500;
    m.laser_.center_.y = 1;
    m.laser_.bullet_ = {5,5};
    CHECK(m.laser_.live_);
    m.update();
    CHECK_FALSE(m.laser_.live_);
}

TEST_CASE("Hits bottom works"){
    Geometry geometry;
    Model m(geometry);

    Hero hero;
    hero.x = 10;
    hero.y = 10;
    hero.width = 5;
    hero.height = 5;
    hero.type = 1;
    hero.live = true;
    hero.shooting = false;
    m.heroes_.clear();
    m.heroes_.push_back(hero);
    m.laser_.live_ = true;
    m.laser_.center_.x = 500;
    m.laser_.center_.y = 768;
    m.laser_.bullet_ = {5,5};
    m.hero_lasers.clear();
    m.hero_lasers.push_back(m.laser_);
    CHECK(m.laser_.hits_bottom(geometry));
}

TEST_CASE("Laser follows player when not live"){
    Geometry geometry;
    Model m(geometry);

    m.laser_.live_ = false;
    m.laser_.center_.x = m.player_.x;
    m.laser_.center_.y = m.player_.y;
    Laser lasercopy = m.laser_;
    m.move_player_right();
    CHECK(m.laser_.center_.x == (lasercopy.center_.x + 20));
}
