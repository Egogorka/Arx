//
// Created by meeve on 02.08.2022.
//

#ifndef ARX_DRAWER_H
#define ARX_DRAWER_H

#include <SFML/Graphics.hpp>
#include "vector/Vector.h"
#include <vector>
#include <memory>


#include "utility/ndarray/ndArrayView.h"
#include "assets/textures/tiles.h"
#include "src/drawer/TileSprite.h"

class Drawer {
protected:
    std::shared_ptr<std::vector<sf::Texture>> textures;
    std::shared_ptr<std::vector<TileSpriteFactory>> factories;

    sf::RenderWindow window;

    static Type getTileType(const ndArrayView<Tiles,2>& tiles, Vector2i position);
    void draw(const sf::Drawable& drawable, const Vector2f& pos, float zlevel, sf::Transform transform = sf::Transform::Identity);
public:
    explicit Drawer(const Vector2i& resolution);

    Vector2f parallax_center{0.5f,0.0f};
    float parallax_offset = 5.0f;
    float parallax_scale = 0.15f;
    float scale = 2;

    bool pollEvent(sf::Event& event);

    void drawTiles(const ndArrayView<Tiles,2>& tiles);
    void drawTiles(const ndArrayView<Tiles,2>& tiles, float zlevel);
    void display();
    void clear();

    template<typename T>
    static sf::Vector2<T> toSFMLvector(Vector<T,2> vector){
        return sf::Vector2<T>{vector[0], vector[1]};
    }

    template<typename T>
    static Vector<T,2> fromSFMLvector(sf::Vector2<T> vector){
        return Vector<T,2>{vector[0], vector[1]};
    }

};


#endif //ARX_DRAWER_H
