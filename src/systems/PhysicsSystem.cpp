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

    // Resolve times
    auto near = (rect.pos - line.p1) * invdir; // top-left cross
    auto far = (rect.pos + rect.size - line.p1) * invdir; // bottom-right cross

    {
        auto temp = line.p2 - line.p1;
        if (temp[0] < 0) std::swap(near.x(), far.x());
        if (temp[1] < 0) std::swap(near.y(), far.y());
    }

#ifdef ARX_DEBUG
    auto nx = line.p1 + near.x() * raydir;
    auto ny = line.p1 + near.y() * raydir;
    auto fx = line.p1 + far.x() * raydir;
    auto fy = line.p1 + far.y() * raydir;

    drawer->draw_circle(nx, 0, sf::Color::Red);
    drawer->draw_circle(ny, 0, sf::Color::Green);
    drawer->draw_circle(fx, 0, sf::Color::White);
    drawer->draw_circle(fy, 0);
#endif

    if( near.x() > far.y() || near.y() > far.x() ) return false;
    // Collision happened

    t = std::max(near.x(), near.y());
    collision_point = line.p1 + t * raydir;

    dir = {0, 0};
    if( near.x() > near.y() ) {
        if (raydir.x() < 0) {
            dir = {1, 0};
        } else
            dir = {-1, 0};
    } else if( near.x() < near.y() ) {
        if( raydir.y() < 0) {
            dir = {0, 1};
        } else
            dir = {0, -1};
    }

#ifdef ARX_DEBUG
    auto size = Vector2f{5,5} * (dir + Vector2f{0.1,0.1});
    drawer->draw_circle(collision_point, 0, sf::Color::Cyan);
    drawer->draw_rect(collision_point, size, 0);
#endif

    return true;
}

bool PhysicsSystem::rectVel_rect_collision(const PhysicsSystem::RectVel &rect1, const PhysicsSystem::Rect &rect2,
                                           sf::Time& time, Vector2f &cp, float &ct, Vector2f &dir) {
    if(rect1.vel == Vector2f{0,0}) return false;

    Rect expanded_rect{
        rect2.pos - rect1.rect.size,
        rect2.size + rect1.rect.size
    };

#ifdef ARX_DEBUG
    drawer->draw_rect(expanded_rect.pos, 32*expanded_rect.size, 0);
#endif

    if(line_rect_collision({rect1.rect.pos, next_pos(rect1.rect.pos, rect1.vel, time)}, expanded_rect, cp, ct, dir))
        return ct <= 1.f && ct >= 0.f;
    return false;
}

bool PhysicsSystem::resolve_collision(PhysicsSystem::RectVel &rect1, const PhysicsSystem::Rect &rect2, sf::Time& time) {
    Vector2f contact_point, contact_normal;
    float contact_time = 0.f;
    if(rectVel_rect_collision(rect1, rect2, time, contact_point, contact_time, contact_normal)){
        rect1.vel += contact_normal * Vector2f{abs(rect1.vel.x()),abs(rect1.vel.y())} * (1 - contact_time);
        return true;
    }
    return false;
}

void PhysicsSystem::update(const ndArrayView<Tiles, 2> &tiles, sf::Time& time) {
    registry->view<LocationC, CollisionC>().each([&](auto entity, LocationC& location, CollisionC& collision){
        Vector2f velocity = location.velocity.getXY();
        Vector2f position = location.position.getXY();

        Rect entityRect{position, collision.size};

        Line line{location.position.getXY(), PhysicsSystem::next_pos(position, velocity, time)};
        auto size = tiles.get_size();

#ifdef ARX_DEBUG
        drawer->draw_rect(location.position.getXY(), 32*collision.size, location.position.z());
#endif

        auto tile_size = Vector2f{1,1};
        for(int x = 0; x < size[0]; x++){
            for(int y = 0; y < size[1]; y++){
                Vector2i pos{x,y};
                if(tiles[pos] != Tiles::Brick) continue;

                Rect rect{get_vector_i2f(pos), tile_size};
                RectVel rectVel{entityRect, velocity};

                if(resolve_collision(rectVel, rect, time)){
                    std::cout << "collision!\n";
                }
            }
        }
        location.velocity.x() = velocity.x(); location.velocity.y() = velocity.y();
        auto next_pos = PhysicsSystem::next_pos(position, velocity, time);
        location.position.x() = next_pos.x(); location.position.y() = next_pos.y();
    });
}
