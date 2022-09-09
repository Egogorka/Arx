//
// Created by Meevere on 04.09.2022.
//

#include "PhysicsSystem.h"

#include "src/components/LocationC.h"
#include "src/components/CollisionC.h"

PhysicsSystem::PhysicsSystem(entt::registry *registry) : registry(registry) {}

bool PhysicsSystem::line_rect_collision(const PhysicsSystem::PointLine &line, const PhysicsSystem::Rect &rect,
                                        Vector2f &collision_point, float &t, Vector2f& dir, Drawer& drawer) {
    if(line.p1 == line.p2) return false;

    auto nx = line.vline_cross(rect.pos[0]);
    auto fx = line.vline_cross((rect.pos + rect.size)[0]);
    auto ny = line.hline_cross(rect.pos[1]);
    auto fy = line.hline_cross((rect.pos + rect.size)[1]);

    {
        auto temp = line.p2 - line.p1;
        if (temp[0] < 0) std::swap(nx, fx);
        if (temp[1] < 0) std::swap(ny, fy);
    }

    drawer.draw_circle(nx.pt, 0);
    drawer.draw_circle(fx.pt, 0);
    drawer.draw_circle(ny.pt, 0);
    drawer.draw_circle(fy.pt, 0);

    if( nx.t > fy.t || ny.t > fx.t ) return false;

    // Collision happened

    if( nx.t > ny.t ) std::swap(nx, ny);
    collision_point = ny.pt; t = ny.t;

    drawer.draw_circle(collision_point, 0, sf::Color::Cyan);

    return true;
}

void PhysicsSystem::update(const ndArrayView<Tiles, 2> &tiles, sf::Time& time, Drawer& drawer) {
    registry->view<LocationC, CollisionC>().each([&](auto entity, LocationC& location, CollisionC& collision){
        Vector2f next_pos = ((location.position + location.velocity / 16 * time.asMilliseconds()) ).getXY();
        PointLine line{location.position.getXY(), next_pos};
        auto size = tiles.get_size();

        auto tile_size = Vector2f{1,1};
        for(int x = 0; x < size[0]; x++){
            for(int y = 0; y < size[1]; y++){
                Vector2i pos{x,y};
                if(tiles[pos] != Tiles::Brick) continue;

                Rect rect{ get_vector_i2f(pos) - collision.size/32, tile_size + collision.size/32 };
//                std::cout << rect.pos << " / " << rect.size << " -> " << location.position << '\n';
                float t; Vector2f temp;
//                std::cout << "collide check\n";
                if(line_rect_collision(line, rect, temp, t, drawer) && t < 1.f && t > 0.f){
                    std::cout << "collide!\n";

                }
            }
        }
        location.position.x() = next_pos.x(); location.position.y() = next_pos.y();
    });
}

std::ostream &operator<<(std::ostream &out, const PhysicsSystem::PointFloat &vec) {
    out << vec.pt << ' ' << vec.t;
    return out;
}

PhysicsSystem::PointFloat PhysicsSystem::PointLine::vline_cross(float a) const {
    auto t = (a - p1[0])/(p2[0] - p1[0]);
    return {p1 + (p2-p1)*t, t};
}

PhysicsSystem::PointFloat PhysicsSystem::PointLine::hline_cross(float a) const {
    auto t = (a - p1[1]) / (p2[1] - p1[1]);
    return {p1 + (p2 - p1) * t, t};
}
