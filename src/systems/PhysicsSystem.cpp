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

    // Check if line crosses rectangle
    if( near.x() > far.y() || near.y() > far.x() ) return false;

    // Check if interval is inside of it
    auto far_t = std::min(far.x(), far.y());
    auto near_t = std::max(near.x(), near.y());

    if( near_t > 1.f ) return false;
    if( far_t  < 0.f ) return false;

    t = near_t;

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
        Vector2f colbox_pos = position + collision.offset/32;
        auto next_pos = PhysicsSystem::next_pos(position, velocity, time);

        Rect entityRect{colbox_pos, collision.size/32};

        Line line{position, next_pos};

        auto size = tiles.get_size();
        auto tile_size = Vector2f{1,1};

#ifdef ARX_DEBUG
        drawer->draw_rect(entityRect.pos, 32*entityRect.size, location.position.z());
#endif
        auto [f_top_left, f_bottom_right] = bounding_box({entityRect, velocity}, time);

        f_top_left += Vector2f{-.1f,-.1f};
        f_bottom_right += Vector2f{.1f,.1f};

        Vector2i top_left{(int)floorf(f_top_left.x()),(int)floorf(f_top_left.y())};
        Vector2i bottom_right{(int)floorf(f_bottom_right.x()+1), (int)floorf(f_bottom_right.y()+1)};

#ifdef ARX_DEBUG
        drawer->draw_rect(get_vector_i2f(top_left), 32*get_vector_i2f(bottom_right-top_left), location.position.z(), sf::Color::Green);
#endif

        for(int x = std::max(0, top_left.x()); x < size[0] && x < bottom_right.x(); x++){
            for(int y = std::max(0, top_left.y()); y < size[1] && y < bottom_right.y(); y++){
                Vector2i pos{x,y};
                if(tiles[pos] != Tiles::Brick) continue;

                Rect rect{get_vector_i2f(pos), tile_size};
                RectVel rectVel{entityRect, velocity};

                if(resolve_collision(rectVel, rect, time)){
                    std::cout << "collision!\n";
#ifdef ARX_DEBUG
                    drawer->draw_rect(rect.pos, 32*rect.size, location.position.z(), sf::Color::Green);
#endif
                }
            }
        }
        location.velocity.x() = velocity.x(); location.velocity.y() = velocity.y();
        next_pos = PhysicsSystem::next_pos(position, velocity, time);
        location.position.x() = next_pos.x(); location.position.y() = next_pos.y();
    });
}

std::tuple<Vector2f,Vector2f> PhysicsSystem::bounding_box(const PhysicsSystem::RectVel &rect, sf::Time& time) {
    Rect next_rect{next_pos(rect.rect.pos, rect.vel, time), rect.rect.size};

    auto pos2 = rect.rect.pos + rect.rect.size;
    auto next_pos2 = next_rect.pos + next_rect.size;

    auto top_left = Vector2f{
        std::min({rect.rect.pos.x(),pos2.x(),next_rect.pos.x(),next_pos2.x()}),
        std::min({rect.rect.pos.y(),pos2.y(),next_rect.pos.y(),next_pos2.y()}),
    };

    auto bottom_right = Vector2f{
            std::max({rect.rect.pos.x(),pos2.x(),next_rect.pos.x(),next_pos2.x()}),
            std::max({rect.rect.pos.y(),pos2.y(),next_rect.pos.y(),next_pos2.y()}),
    };

    return {top_left, bottom_right};
}
