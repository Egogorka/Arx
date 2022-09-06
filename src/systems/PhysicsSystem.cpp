//
// Created by Meevere on 04.09.2022.
//

#include "PhysicsSystem.h"

#include "src/components/LocationC.h"
#include "src/components/CollisionC.h"

struct PointFloat {
    Vector2f pt;
    float t;

    friend std::ostream& operator<<(std::ostream& out, const PointFloat& vec){
        out << vec.pt << ' ' << vec.t;
        return out;
    }
};

struct PointLine {
    Vector2f p1;
    Vector2f p2;

    PointFloat vline_cross(float a) const{
        auto t = (a - p1[0])/(p2[0] - p1[0]);
        return {p1 + (p2-p1)*t, t};
    }
    PointFloat hline_cross(float a) const {
        auto t = (a - p1[1]) / (p2[1] - p1[1]);
        return {p1 + (p2 - p1) * t, t};
    }
};

struct Rect {
    Vector2f pos;
    Vector2f size;
};

bool line_rect_collision(const PointLine& line, const Rect& rect, Vector2f& collision_point, float& t){
    if(line.p1 == line.p2) return false;

    auto nx = line.vline_cross(rect.pos[0]);
    auto fx = line.vline_cross((rect.pos + rect.size)[0]);
    auto ny = line.hline_cross(rect.pos[1]);
    auto fy = line.hline_cross((rect.pos + rect.size)[1]);
    std::cout << nx.pt << ' ' << fx.pt << '|' << ny.pt << ' ' << fy.pt << '\n';
    std::cout << nx.t << ' ' << fx.t << '|' << ny.t << ' ' << fy.t << '\n';
    {
        auto temp = line.p2 - line.p1;
        if (temp[0] < 0) std::swap(nx, fx);
        if (temp[1] < 0) std::swap(ny, fy);
    }

    if( nx.t > fy.t || ny.t > fx.t ) return false;

    // Collision happened

    if( nx.t > ny.t ) std::swap(nx, ny);
    collision_point = ny.pt; t = ny.t;
    return true;
}

void PhysicsSystem::update(entt::registry &registry, const ndArrayView<Tiles, 2> &tiles, sf::Time& time) {
    registry.view<LocationC, CollisionC>().each([&](auto entity, LocationC& location, CollisionC& collision){
        Vector2f next_pos = ((location.position + location.velocity / 16 * time.asMilliseconds()) ).getXY();
        PointLine line{location.position.getXY(), next_pos};
        auto size = tiles.get_size();

        auto tile_size = Vector2f{1,1};
        for(int x = 0; x < size[0]; x++){
            for(int y = 0; y < size[1]; y++){
                Vector2i pos{x,y};
                if(tiles[pos] != Tiles::Brick) continue;

                Rect rect{ get_vector_i2f(pos) - collision.size/32, tile_size + collision.size/32 };
                std::cout << rect.pos << " / " << rect.size << " -> " << location.position << '\n';
                float t; Vector2f temp;
                std::cout << "collide check\n";
                if(line_rect_collision(line, rect, temp, t) && t < 1.f && t > 0.f){
                    std::cout << "collide!\n";
                    next_pos = temp;
                }
            }
        }
        location.position.x() = next_pos.x(); location.position.y() = next_pos.y();
    });
}
