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

void Drawer::drawTiles(const ndArrayView<Tiles, 2>& tiles, float zlevel) {
    auto size = tiles.get_size();
    for(int x = 0; x < size[0]; x++){
        for(int y = 0; y < size[1]; y++){
            Vector2i pos{x,y};
            if(tiles[pos] == Tiles::None) continue;
            auto type = getTileType(tiles, pos);
            auto tile = factories->at(static_cast<int>(tiles[pos])).getTileSprite(type);

            tile.setScale(scale,scale);

//            sf::Transform transform;
//            transform.translate(float(64*x), float(64*y));
//            transform.scale(1,1);
//            transform.rotate(45);
//            window.draw(tile, transform);
            draw(tile, get_vector_i2f(32*scale*pos), zlevel);
        }
    }
}

void Drawer::drawTiles(const ndArrayView<Tiles, 2> &tiles) {
    drawTiles(tiles, 0.f);
}

void Drawer::display() {
    window.display();
}

void Drawer::clear() {
    window.clear();
}

bool Drawer::pollEvent(sf::Event &event) {
    return window.pollEvent(event);
}

void Drawer::draw(const sf::Drawable& drawable, const Vector2f& pos, float zlevel, sf::Transform transform) {
    // Calculate the transform
    auto z_scale = parallax_offset / (parallax_scale * zlevel + parallax_offset);
    auto parallax_pos = Vector2f{parallax_center[0]*window.getSize().x, parallax_center[1]*window.getSize().y};
    sf::Transform parallax_transform = transform;

    auto offset = pos * z_scale + (parallax_pos) * (1 - z_scale);

    parallax_transform.translate(toSFMLvector(offset));
    parallax_transform.scale(z_scale, z_scale);

    sf::RenderStates states;
    states.transform = parallax_transform;

    window.draw(drawable, parallax_transform);
}