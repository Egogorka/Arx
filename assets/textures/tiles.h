//
// Created by Meevere on 07.08.2022.
//

#ifndef ARX_ASSETS_TEXTURES_TILES_H
#define ARX_ASSETS_TEXTURES_TILES_H

#include <map>

enum class Tiles {
    None = -1,
    Brick = 0,
    RotatableTiles = Brick,
};

extern std::map<std::string, Tiles> tilesMap;

#endif //ARX_ASSETS_TEXTURES_TILES_H
