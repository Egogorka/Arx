//
// Created by meeve on 02.08.2022.
//

#include "Drawer.h"
#include "utility/vector/sfConvert.h"

Drawer::Drawer(const Vector2i &resolution)
{
    window.create(sf::VideoMode(resolution.x(), resolution.y()), "Arx", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Drawer::display() {

    window.display();
}

void Drawer::clear() {
    // this.sprites is either emptied or left as it is
    sprites.resize(0);

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

    // times 32 because 1 = 1 tile

    auto offset = (32*scale*pos) * z_scale + (parallax_pos) * (1 - z_scale);

    parallax_transform.translate(toSFMLvector(offset));
    parallax_transform.scale(z_scale, z_scale);
    parallax_transform.scale(scale, scale);

    sf::RenderStates states;
    states.transform = parallax_transform;

    window.draw(drawable, parallax_transform);
}

void Drawer::draw(const sf::Drawable &drawable, const Vector3f &pos, sf::Transform transform) {
    draw(drawable, pos.getXY(), pos.z(), transform);
}

void Drawer::reserve_queue(int n) {
    sprites.reserve(n);
}

void Drawer::queue(const sf::Sprite &drawable, const Vector2f &pos, float zlevel, sf::Transform transform) {
    ZSprite temp{drawable, zlevel, pos, transform};
    sprites.insert(std::upper_bound(sprites.begin(), sprites.end(), temp), temp);
}

void Drawer::queue(const sf::Sprite &drawable, const Vector3f &pos, sf::Transform transform) {
    queue(drawable, pos.getXY(), pos.z(), transform);
}

void Drawer::display_sprites(const std::function<void(int)> &callback, int start_level, int end_level) {
    for(auto& item: sprites) {
        while (start_level >= int(item.zlevel) && start_level >= end_level){
            callback(start_level);
            start_level--;
        }
        draw(item.sprite, item.pos, item.zlevel, item.transform);
    }
    while( start_level >= end_level) {
        callback(start_level);
        start_level--;
    }
}

void Drawer::draw_circle(const Vector2f &pos, float zlevel, sf::Color color, float radius) {
    sf::CircleShape circle{radius};
    circle.setFillColor(color);
    draw(circle, pos, zlevel);
}

void Drawer::draw_rect(const Vector2f &pos, const Vector2f &size, float zlevel, sf::Color color, float width) {
    auto temp = pos;
    if(size.x() < 0){
        temp.x() += size.x();
    }
    if(size.y() < 0){
        temp.y() += size.y();
    }
    sf::RectangleShape rect{toSFMLvector(size)};
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(color);
    rect.setOutlineThickness(width);
    draw(rect, temp, zlevel);
}

//void Drawer::draw_line(const Vector2f &pos1, const Vector2f &pos2, float zlevel, sf::Color color, float width) {
//    auto d = pos2-pos1;
//    sf::RectangleShape rect{sf::Vector2f{sqrtf(Vector2f::square(d)),width}};
//    rect.setFillColor(color);
//
//    float angle = atanf(d.y()/d.x());
//    angle += d.x() > 0 ? 180. : 0.;
//    rect.rotate(angle);
//
//    draw(rect, pos1, zlevel);
//}

bool Drawer::ZSprite::operator<(const Drawer::ZSprite &rhs) const { return zlevel > rhs.zlevel; }
bool Drawer::ZSprite::operator>(const Drawer::ZSprite &rhs) const { return rhs < *this; }
bool Drawer::ZSprite::operator<=(const Drawer::ZSprite &rhs) const { return !(rhs < *this); }
bool Drawer::ZSprite::operator>=(const Drawer::ZSprite &rhs) const { return !(*this < rhs); }
