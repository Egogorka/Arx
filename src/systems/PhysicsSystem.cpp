//
// Created by Meevere on 04.09.2022.
//

#include "PhysicsSystem.h"

#include "src/components/LocationC.h"
#include "src/components/CollisionC.h"

#ifndef ARX_DEBUG
PhysicsSystem::PhysicsSystem(entt::registry *registry) : registry(registry) {}
#else
PhysicsSystem::PhysicsSystem(entt::registry *registry, Drawer *drawer) : registry(registry), drawer(drawer) {}
#endif


bool PhysicsSystem::line_rect_collision(const PhysicsSystem::Line &line, const PhysicsSystem::Rect &rect,
                                        Vector2f &collision_point, float &t, Vector2f& dir) {
    if(line.p1 == line.p2) return false;

    auto raydir = line.p2 - line.p1;
    auto invdir = 1.f / raydir;

    auto near = (rect.pos - line.p1) * invdir;
    auto far  = (rect.pos + rect.size - line.p1) * invdir;

    {
        auto temp = line.p2 - line.p1;
        if (temp[0] < 0) std::swap(near.x(), far.x());
        if (temp[1] < 0) std::swap(near.y(), far.y());
    }

#ifdef ARX_DEBUG
    drawer->draw_circle(nx.pt, 0);
    drawer->draw_circle(fx.pt, 0);
    drawer->draw_circle(ny.pt, 0);
    drawer->draw_circle(fy.pt, 0);
#endif

    if( nx.t > fy.t || ny.t > fx.t ) return false;
    // Collision happened

    if( nx.pt.y() <  )

    if( ny.t < nx.t ) std::swap(nx, ny);
    collision_point = ny.pt; t = ny.t; // return max(nx,ny)

#ifdef ARX_DEBUG
    drawer->draw_circle(collision_point, 0, sf::Color::Cyan);
#endif

    return true;
}

void PhysicsSystem::update(const ndArrayView<Tiles, 2> &tiles, sf::Time& time) {
    registry->view<LocationC, CollisionC>().each([&](auto entity, LocationC& location, CollisionC& collision){
        Vector2f next_pos = ((location.position + location.velocity / 16 * time.asMilliseconds()) ).getXY();

        Line line{location.position.getXY(), next_pos};
        auto size = tiles.get_size();

#ifdef ARX_DEBUG
        drawer->draw_rect(location.position.getXY(), collision.size, location.position.z());
#endif

        auto tile_size = Vector2f{1,1};
        for(int x = 0; x < size[0]; x++){
            for(int y = 0; y < size[1]; y++){
                Vector2i pos{x,y};
                if(tiles[pos] != Tiles::Brick) continue;

                Rect rect{ get_vector_i2f(pos) - collision.size/32, tile_size + collision.size/32 };

                float t{}; Vector2f temp, dir;
                if(line_rect_collision(line, rect, temp, t, dir) && t < 1.f && t > 0.f){
                    std::cout << "collide!\n";
                    next_pos = temp;
                    location.velocity = Vector3f{0,0,0};
                }
                std::cout << t << '\n';
            }
        }
        location.position.x() = next_pos.x(); location.position.y() = next_pos.y();
    });
}

bool PhysicsSystem::resolve_collision(const PhysicsSystem::Line) {
    return false;
}

PhysicsSystem::PointNTime PhysicsSystem::Line::vline_cross(float a) const {
    auto t = (a - p1[0])/(p2[0] - p1[0]);
    return {p1 + (p2-p1)*t, t};
}

PhysicsSystem::PointNTime PhysicsSystem::Line::hline_cross(float a) const {
    auto t = (a - p1[1]) / (p2[1] - p1[1]);
    return {p1 + (p2 - p1) * t, t};
}
