//
// Created by Meevere on 04.09.2022.
//

#ifndef ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
#define ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H

#include "include/entt.hpp"

#include "utility/ndarray/ndArrayView.h"
#include "assets/tiles.h"

#include <SFML/Graphics.hpp>

// For debug
#include "Drawer.h"

/**
 * Handles moving and collisions
 */
class PhysicsSystem {
    entt::registry *registry;

public:
    explicit PhysicsSystem(entt::registry *registry);

    void update(const ndArrayView<Tiles, 2> &tiles, sf::Time& time, Drawer& drawer);

public:
    struct PointFloat {
        Vector2f pt;
        float t;

        friend std::ostream& operator<<(std::ostream& out, const PointFloat& vec);
    };

private:
    struct Rect {
        Vector2f pos;
        Vector2f size;
    };

    struct PointLine {
        Vector2f p1;
        Vector2f p2;

        [[nodiscard]] PointFloat vline_cross(float a) const;
        [[nodiscard]] PointFloat hline_cross(float a) const;
    };

    bool line_rect_collision(const PointLine& line, const Rect& rect, Vector2f& collision_point, float& t, Vector2f& dir, Drawer& drawer);
};


#endif //ARX_SRC_SYSTEMS_COLLISIONSYSTEM_H
