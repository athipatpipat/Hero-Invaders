#include "model.h"
#include <catch.h>

TEST_CASE("Hero moves faster when one hero dies"){
    Geometry geometry;
    Model m(geometry);
    Hero hero1{5,5,10,10};

    m.heroes_.push_back(hero1);

    CHECK(m.hero_velocity == 1);

    Laser laser1(m.player_, geometry);
    laser1.live_ == true;
    laser1.center_.x = 5;
    laser1.center_.y = 5;
    laser1.bullet_ = {5,5};
    m.update();
    CHECK(m.hero_velocity == 1.1 );



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
    Laser laser(m.player_, geometry);
    laser.live_ = true;
    Hero hero1;
    hero1.type = 1;
    hero1.x = 50;
    hero1.y = 20;
    laser.center_.x = 50;
    laser.center_.y = 20;
    m.update();
    CHECK(m.score==30);


}


TEST_CASE("Barrier dies when hit by both player and hero"){

}