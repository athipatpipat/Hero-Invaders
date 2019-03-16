#include "model.h"
#include <catch.h>
#include <math.h>

TEST_CASE("Hero moves faster when one hero dies"){
    Geometry geometry;
    Model m(geometry);
    Hero hero1;

    hero1.x = 300;
    hero1.y = 300;
    hero1.width = 50;
    hero1.height = 50;
    hero1.live = true;
    m.hero_velocity = 1;
    m.heroes_.push_back(hero1);
    CHECK(m.hero_velocity == 1);
    Laser laser1(m.player_, geometry);
    laser1.live_ = true;
    laser1.center_.x = 300;
    laser1.center_.y = 360;
    laser1.bullet_ = {5,5};
    CHECK(laser1.hits_hero(hero1));
    CHECK(laser1.destroy_hero(m.heroes_, m.score, m.hero_velocity));
    m.update();

    //Float cannot be compared using ==
    CHECK(std::fabs(m.hero_velocity - 1.1) < std::numeric_limits<float>::epsilon());

}

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

TEST_CASE("Game Over message when life is zero"){
    Geometry geometry;
    Model m(geometry);
    m.player_lives = 3;
    CHECK_FALSE(m.game_over);
    m.player_lives = 0;
    m.update();
    CHECK(m.game_over);
}


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
    m.heroes_.push_back(hero1);
    m.laser_.destroy_hero(m.heroes_,m.score,m.hero_velocity);
    CHECK(m.laser_.hits_hero(hero1));
    m.update();
    CHECK(m.score==30);

}


TEST_CASE("Barrier dies when hit by both player and hero"){

}