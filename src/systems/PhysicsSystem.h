//
// Created by Meevere on 04.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
#define ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H

#include "include/entt.hpp"

#include "utility/ndarray/ndArrayView.h"
#include "assets/tiles.h"

#include <SFML/Graphics.hpp>

#include "main.h"
#ifdef ARX_DEBUG
#include "Drawer.h"
#endif

/**
 * Handles moving and collisions
 */
class PhysicsSystem {
    entt::registry *registry;
    #ifdef ARX_DEBUG
        Drawer* drawer;
    #endif

public:
    #ifndef ARX_DEBUG
        explicit PhysicsSystem(entt::registry *registry);
    #else
        PhysicsSystem(entt::registry *registry, Drawer* drawer);
    #endif

    void update(const ndArrayView<Tiles, 2> &tiles, sf::Time& time);

private:
    struct PointNTime {
        Vector2f pt;
        float t;
    };

    struct Rect {
        Vector2f pos;
        Vector2f size;
    };

    struct Line {
        Vector2f p1;
        Vector2f p2;

        [[nodiscard]] PointNTime vline_cross(float a) const;
        [[nodiscard]] PointNTime hline_cross(float a) const;
    };

    struct RectVel {
        Rect rect;
        Vector2f vel;
    };

    bool line_rect_collision(const Line& line, const Rect& rect, Vector2f& collision_point, float& t, Vector2f& dir);
    bool resolve_collision(const Line);
};


#endif //ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
