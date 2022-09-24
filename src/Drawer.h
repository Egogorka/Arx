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
#include "assets/tiles.h"
#include "src/drawer/TileSprite.h"


/**
 * This classes purpose is to draw sf::Sprites isometrically
 */
class Drawer {
protected:
    sf::RenderWindow window;

    struct ZSprite {
        sf::Sprite sprite;
        float zlevel;

        Vector2f pos;
        sf::Transform transform;

        bool operator<(const ZSprite &rhs) const;
        bool operator>(const ZSprite &rhs) const;
        bool operator<=(const ZSprite &rhs) const;
        bool operator>=(const ZSprite &rhs) const;
    };

    std::vector<ZSprite> sprites;
public:
    explicit Drawer(const Vector2i& resolution);

    // In tiles
    Vector3f offset{0.f,0.f,0.f};

    Vector2f parallax_center{0.5f,0.0f};
    float parallax_offset = 5.0f;
    float parallax_scale = 0.15f;
    float scale = 2;

    Vector2f get_size();

    bool pollEvent(sf::Event& event); // might need to take this out of the drawer

    void display();
    void clear();

    // Can only queue drawing Sprites (sf::Drawable would be slower cuz pointer)
    void reserve_queue(int n);
    void queue(const sf::Sprite& drawable, const Vector2f& pos, float zlevel, sf::Transform transform = sf::Transform::Identity);
    void queue(const sf::Sprite& drawable, const Vector3f& pos, sf::Transform transform = sf::Transform::Identity);

    /**
     * Displays all of the sprites in this.sprites
     * As the cycle of display goes it calls back each time the integer point is 'crossed'
     * @param callback - function that will be called back each time an integer z-level is met in cycle
     * @param start_level - the starting z-level
     * @param end_level - ending z-level
     */
    void display_sprites(const std::function<void(int)>& callback, int start_level, int end_level);

    // The functions to draw drawables without the z-priorities
    void draw(const sf::Drawable& drawable, const Vector2f& pos, float zlevel, sf::Transform transform = sf::Transform::Identity);
    void draw(const sf::Drawable& drawable, const Vector3f& pos, sf::Transform transform = sf::Transform::Identity);

    // For testing
    void draw_circle(const Vector2f& pos, float zlevel, sf::Color color = sf::Color::Yellow, float radius = 1.0f);
    void draw_rect(const Vector2f& pos, const Vector2f& size, float zlevel, sf::Color color = sf::Color::Red, float width = 1.0f);
//    void draw_line(const Vector2f& pos1, const Vector2f& pos2, float zlevel, sf::Color color = sf::Color::Red, float width = 1.0f);

    void draw_raw(const sf::Drawable& drawable);
};


#endif //ARX_DRAWER_H
