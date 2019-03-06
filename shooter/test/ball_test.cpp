#include "ball.h"
#include "model.h"
#include <catch.h>

Block const paddle{100, 400, 100, 20};

TEST_CASE("Ball::Ball")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK( ball.center_.x == 150 );
    CHECK( ball.center_.y == 394 );
}

TEST_CASE("Ball::hits_side")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK_FALSE( ball.hits_side(geometry) );
    ball.center_.x = 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width - 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width / 2;
    CHECK_FALSE( ball.hits_side(geometry) );
}

TEST_CASE("Ball:hits_bottom"){
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK_FALSE( ball.hits_bottom(geometry) );
    ball.center_.y = geometry.scene_dims.height;
    CHECK(ball.hits_bottom(geometry));
    ball.center_.y = geometry.scene_dims.height/2;
    CHECK_FALSE(ball.hits_bottom(geometry));

}


TEST_CASE("Ball:hits_top"){
    Geometry geometry;
    Ball ball(paddle, geometry);
    CHECK_FALSE( ball.hits_top(geometry) );
    ball.center_.y = 0;
    CHECK(ball.hits_top(geometry));
    ball.center_.y = geometry.scene_dims.height/2;
    CHECK_FALSE(ball.hits_top(geometry));


}
//test that if ball hits two bricks then it destroys only one brick
TEST_CASE("Ball:hits_block"){
    Geometry geometry;
    Block block;
    block.x = geometry.scene_dims.width/2;
    block.y = geometry.scene_dims.height/2;
    block.width = 100;
    block.height = 100;
    Ball ball(paddle, geometry);
    ball.center_.x = block.x-ball.radius_;
    ball.center_.y = block.y;
    CHECK( ball.hits_block(block) );


    CHECK( ball.hits_block(block) );
    ball.center_.x = block.x+200;
    ball.center_.y = block.y+200;
    CHECK_FALSE( ball.hits_block(block) );
}


TEST_CASE("Ball:destroy_brick"){
    Geometry geometry;
    Ball ball(paddle, geometry);
    Model model;
    ball.center_.y = geometry.scene_dims.height;
    ball.center_.x = geometry.scene_dims.width/2;
    CHECK_FALSE(ball.destroy_brick(model.bricks_));
    ball.center_.x = model.bricks_.at(2).x;
    ball.center_.y = model.bricks_.at(2).y;
    CHECK(ball.destroy_brick(model.bricks_));
    ball.center_.y = geometry.scene_dims.height;
    ball.center_.x = geometry.scene_dims.width/2;
    CHECK_FALSE(ball.destroy_brick(model.bricks_));




}
TEST_CASE("Ball:destroy_brick2"){
    Geometry geometry;
    Ball ball(paddle, geometry);
    Model model;
    Block brick1;
    brick1.x = 1;
    brick1.y = 1;
    brick1.width = 2;
    brick1.height = 2;
    Block brick2;
    brick1.x = 1;
    brick1.y = 1;
    brick1.width = 2;
    brick1.height = 2;

    std::vector<Block> bricks{brick1,brick2};

    ball.radius_ = 2;
    ball.center_.y = 1;
    ball.center_.x = 1;
    ball.destroy_brick(bricks);
    CHECK(bricks.size() == 1);

}


TEST_CASE("Ball:reflect_vertical"){
    Geometry geometry;
    Ball ball(paddle, geometry);
    ball.velocity_={2,3};
    ball.reflect_vertical();
    CHECK(ball.velocity_.height == -3);

}

TEST_CASE("Ball:reflect_horizontal"){
    Geometry geometry;
    Ball ball(paddle, geometry);
    ball.velocity_={2,3};
    ball.reflect_horizontal();
    CHECK(ball.velocity_.width == -2);
}




