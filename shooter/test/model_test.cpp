#include "model.h"
#include <catch.h>

#include "model.h"
#include <catch.h>

TEST_CASE("Hero moves faster when one hero dies"){
    Geometry geometry;
    Model m(geometry);
    Hero hero1{1,1,1,1};
    Hero hero2{1,1,1,1};
    m.heroes_.push_back(hero1);
    m.heroes_.push_back(hero2);

}

TEST_CASE("Player loses one life when hit"){
    Geometry geometry;
    Model m(geometry);

    m.player_.x = 50;
    m.player_.y = 60;

    CHECK(m.player_lives == 3);

    Hero hero1;
    hero1.type = 1;
    hero1.x = 50;
    hero1.y = 55;
    m.heroes_.push_back(hero1);

    Laser hero_laser(hero1, geometry);
    m.hero_shoot();
    m.hero_shoot();
    m.hero_shoot();
    m.hero_shoot();
    m.hero_shoot();

    CHECK(m.player_lives == 2);
}

TEST_CASE("Game Over message when life is zero"){
    Geometry geometry;
    Model m(geometry);
    m.player_lives = 3;
    CHECK_FALSE(m.game_over);
    m.player_lives = 0;
    CHECK(m.game_over);
}


TEST_CASE("Different types of hero give different points when killed "){
    Geometry geometry;
    Model m(geometry);

    m.player_.x = 50;
    Laser laser(m.player_, geometry);

    Hero hero1;
    hero1.type = 1;
    hero1.x = 50;
    hero1.y = 20;
    m.launch();
    while(hero1.live){
        m.update();
    }
    CHECK(m.score==30);

    Hero hero2;
    hero2.type = 2;
    hero2.x = 50;
    hero2.y = 20;
    m.launch();
    while(hero2.live){
        m.update();
    }
    CHECK(m.score==50);

    Hero hero3;
    hero3.type = 3;
    hero3.x = 50;
    hero3.y = 20;
    m.launch();
    while(hero3.live){
        m.update();
    }
    CHECK(m.score==60);

}


TEST_CASE("Barrier dies when hit by both player and hero"){

}