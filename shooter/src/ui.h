#pragma once

#include "model.h"
#include <ge211.h>



///
/// VIEW CONSTANTS
///


using Block = ge211::Rectangle;
// These constants are defined in `ui.cpp` but declared here so that
// we care refer to them when initializing the sprites below.
//
// The keyword `extern` is what prevents this declaration from being
// a definition. That is, this declaration informs subsequent code about
// the existence of these constants without actually defining them here.
extern ge211::Color const ball_color, paddle_color, barrier_color;

struct Ui : ge211::Abstract_game
{

    // Constructs a `Ui` given a reference to the model that stores
    // the actual state of the game.
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby you could pass a `Model` to a function
    // that expects a `Ui` and have it work.
    explicit Ui(Model&);

    // Returns the size of the window as given by `geometry_.scene_dims`.
    //
    // (GE211 calls this to find out how big to make the window.)
    ge211::Dimensions initial_window_dimensions() const override;

    // Renders all the game entities to the screen. In particular,
    // ball_sprite_ is placed at the ball's bounding box's top-left,
    // paddle_sprite_ is placed where the model says the paddle is,
    // and brick_sprite_ is placed for each brick in model_.bricks.
    void draw(ge211::Sprite_set&) override;

    void on_key(ge211::Key) override;

    void on_frame(double dt) override;

    // This is a reference to the model. It means that the UI doesn't
    // own the model but has access to it. Thus, the client of the UI
    // (brick_out.cpp) must create a `Model` first and then pass that by
    // reference to the `Ui` constructor.
    Model& model_;



    ge211::Circle_sprite    const
            ball_sprite_    {model_.geometry_.ball_radius,  ball_color};

    ge211::Rectangle_sprite const
            laser_sprite_ {model_.geometry_.laser_dims_, ball_color};

    ge211::Rectangle_sprite const
            player_sprite_  {model_.geometry_.player_dims_, paddle_color};

    ge211::Rectangle_sprite const
            barrier_sprite_ {model_.geometry_.barrier_dims, barrier_color};

    ge211::Image_sprite batman_{"batman.png"};
    double sprite_scale_width = .2;
    double sprite_scale_height = .15;
    ge211::Text_sprite score_;
    ge211::Text_sprite lives_;
    ge211::Text_sprite game_over_msg;
    //= ge211::Text_sprite("Hello",ge211::Font("sans.ttf",20));

    ge211::Image_sprite deadpool_{"deadpool.png"};
    ge211::Image_sprite turtle_{"turtle.png"};
    ge211::Image_sprite thanos_{"thanos.png"};
    double thanos_scale = .2;

    ge211::Timer timer_;



};
