//
// Created by meeve on 24.08.2022.
//

#ifndef TILES_H_SRC_SYSTEMS_TILESYSTEM_H
#define TILES_H_SRC_SYSTEMS_TILESYSTEM_H

#include <SFML/Graphics.hpp>
#include "vector/Vector.h"
#include <vector>
#include <memory>

#include "utility/ndarray/ndArrayView.h"
#include "assets/textures/tiles.h"
#include "src/drawer/TileSprite.h"

#include "src/Drawer.h"

class TileSystem {
    std::shared_ptr<std::vector<sf::Texture>> tile_textures;
    std::shared_ptr<std::vector<TileSpriteFactory>> factories;

    static Type getTileType(const ndArrayView<Tiles,2>& tiles, Vector2i position);

public:
    TileSystem();

//    void render(const ndArrayView<Tiles,3>& tiles); // if I implement render-queue for Drawer then it would be okay
    void render_partial( const ndArrayView<Tiles,2>& tiles, float zlevel, Drawer& drawer);

};



#endif //TILES_H_SRC_SYSTEMS_TILESYSTEM_H
