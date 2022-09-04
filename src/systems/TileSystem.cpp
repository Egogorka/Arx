//
// Created by meeve on 24.08.2022.
//

#include "TileSystem.h"

#include "assets/textures/static/l.h"

TileSystem::TileSystem() {
    tile_textures = load_static_textures();
    factories = init_factories(tile_textures);
}

Type TileSystem::getTileType(const ndArrayView<Tiles, 2> &tiles, Vector2i position) {
    uint8_t neighbors = 0;
    auto cur_tile = tiles[position];
    neighbors |= tiles.at_def(position + Vector2i{-1,0}, cur_tile) == cur_tile;
    for(int i = -1; i <= 1; i++){
        neighbors |= (tiles.at_def(position + Vector2i{i,-1}, cur_tile) == cur_tile) << (i+2);
    }
    neighbors |= (tiles.at_def(position + Vector2i{1,0}, cur_tile) == cur_tile) << 4;
    for(int i = 1; i >= -1; i--){
        neighbors |= (tiles.at_def(position + Vector2i{i,1}, cur_tile) == cur_tile) << (6-i);
    }
    return Type(neighbors);
}

void TileSystem::render_partial(const ndArrayView<Tiles, 2> &tiles, float zlevel, Drawer &drawer) {
    auto size = tiles.get_size();
    for(int x = 0; x < size[0]; x++){
        for(int y = 0; y < size[1]; y++){
            Vector2i pos{x,y};
            if(tiles[pos] == Tiles::None) continue;
            auto type = getTileType(tiles, pos);
            auto tile = factories->at(static_cast<int>(tiles[pos])).getTileSprite(type);
            drawer.draw(tile, get_vector_i2f(pos), zlevel);
        }
    }
}
