#include "model.h"
#include <catch.h>

TEST_CASE("play the game")
{
    Geometry geometry;
    Model m(geometry);
    CHECK( m.bricks_.size() == 100 );

    m.ball_.live_ = true;
    Ball old_ball = m.ball_;

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 2 * old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 3 * old_ball.velocity_ );
}

TEST_CASE("destroy one brick")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {300, 400};
    m.ball_.velocity_ = {0, -50};

    Ball ball(m.ball_);

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.bricks_.size() == 1 );

    m.update(0);
    ball.velocity_ *= -1;
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.bricks_.empty() );
}
