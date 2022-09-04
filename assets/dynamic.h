//
// Created by meeve on 24.08.2022.
//

#ifndef TILES_H_ASSETS_TEXTURES_DYNAMIC_DYNAMIC_H
#define TILES_H_ASSETS_TEXTURES_DYNAMIC_DYNAMIC_H

#include <nlohmann/json.hpp>

enum class Sprites {
    Pedestal = 0,
    Player,
};

namespace Sprites_ {
    enum class Pedestal {
        Static = 0,
        Falling
    };

    enum class Player {
        Idle = 0,
    };
}

NLOHMANN_JSON_SERIALIZE_ENUM( Sprites, {
    {Sprites::Pedestal, "pedestal"},
    {Sprites::Player, "player"},
})

#endif //TILES_H_ASSETS_TEXTURES_DYNAMIC_DYNAMIC_H
