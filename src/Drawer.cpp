//
// Created by meeve on 02.08.2022.
//

#include "Drawer.h"
#include "assets/textures/l.h"

Drawer::Drawer(const Vector2i &resolution)
: textures(load_textures()), factories(init_factories(textures))
{
    window.create(sf::VideoMode(resolution.x(), resolution.y()), "Arx", sf::Style::Default);
    window.setFramerateLimit(60);
}

Type Drawer::getTileType(const ndArrayView<Tiles, 2> &tiles, Vector2i position) {
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

void Drawer::drawTiles(const ndArrayView<Tiles, 2>& tiles) {
    auto size = tiles.get_size();
    for(int x = 0; x < size[0]; x++){
        for(int y = 0; y < size[1]; y++){
            Vector2i pos{x,y};
            auto type = getTileType(tiles, pos);
            auto tile = factories->at(static_cast<int>(tiles[pos])).getTileSprite(type);

            sf::Transform transform;
            transform.translate(float(32*x), float(32*y));
            window.draw(tile, transform);
        }
    }
}
