#pragma once

#include "model.h"
#include <ge211.h>

///
/// VIEW CONSTANTS
///

using Block = ge211::Rectangle;

extern ge211::Color const barrier_color, laser_color, player_color;

struct Ui : ge211::Abstract_game
{
    // Constructs a `Ui` given a reference to the model that stores
    // the actual state of the game.

    explicit Ui(Model&);

    // Returns the size of the window as given by `geometry_.scene_dims`
    // (GE211 calls this to find out how big to make the window.)
    ge211::Dimensions initial_window_dimensions() const override;

    // Renders all the game entities to the screen.
    void draw(ge211::Sprite_set&) override;

    // Used to move player sprite
    void on_key(ge211::Key) override;

    // Used to update game every frame
    void on_frame(double dt) override;

    //reference to the model.
    Model& model_;


    //Sprite for laser, player, and barrier
    ge211::Rectangle_sprite const
            laser_sprite_ {model_.geometry_.laser_dims_, laser_color};

    ge211::Rectangle_sprite const
            player_sprite_  {model_.geometry_.player_dims_, player_color};

    ge211::Rectangle_sprite const
            barrier_sprite_ {model_.geometry_.barrier_dims, barrier_color};

    //Text on the screen
    ge211::Text_sprite score_;
    ge211::Text_sprite lives_;
    ge211::Text_sprite game_over_msg;

    //Hero sprites
    ge211::Image_sprite batman_{"batman.png"};
    ge211::Image_sprite deadpool_{"deadpool.png"};
    ge211::Image_sprite turtle_{"turtle.png"};
    ge211::Image_sprite thanos_{"thanos.png"};

    //Scaling variables
    double thanos_scale = .2;
    double sprite_scale_width = .2;
    double sprite_scale_height = .15;

    //Timer used to track when random heroes are ramdomly selected to shoot
    ge211::Timer timer_;

};
