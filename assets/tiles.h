//
// Created by Meevere on 07.08.2022.
//

#ifndef ARX_ASSETS_TEXTURES_TILES_H
#define ARX_ASSETS_TEXTURES_TILES_H

#include <map>
#include <nlohmann/json.hpp>

enum class Tiles {
    None = -1,
    Brick = 0,
    Pollution,
    Grass,
    RotatableTiles = Brick,
};

NLOHMANN_JSON_SERIALIZE_ENUM( Tiles, {
    {Tiles::None, "none"},
    {Tiles::Brick, "brick"},
    {Tiles::Grass, "grass"},
    {Tiles::Pollution, "pollution"}
})

#endif //ARX_ASSETS_TEXTURES_TILES_H
