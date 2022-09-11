//
// Created by Meevere on 11.09.2022.
//

#include "utility/vector/Vector.h"

#include <gtest/gtest.h>

TEST(vector_test, elementwise_operations){
    auto v1 = Vector2f::all(1.f);
    auto v2 = Vector2f{2,3};

    ASSERT_NE(v1, v2);

    auto v3 = v1 / v2;
    auto v4 = v3;

    ASSERT_FLOAT_EQ(v3.x(), 1./2);
    ASSERT_FLOAT_EQ(v3.y(), 1./3);

    v3 *= v2;
    ASSERT_EQ(v3, v1);
    v3 /= v2;
    ASSERT_EQ(v3, v4);

    // Test collision points
    Vector2f rect_pos{3,4};
    Vector2f rect_size{1,1};

    Vector2f p1{1,0};
    Vector2f p2{2,1};

    auto raydir = p2 - p1;
    auto invdir = 1.f / raydir;
    ASSERT_EQ(invdir, raydir); // cuz 1.f/1 = 1.f

    auto near = (rect_pos - p1) * invdir;
    ASSERT_FLOAT_EQ(near.x(), 2);
    ASSERT_FLOAT_EQ(near.y(), 4);

    auto far = (rect_pos + rect_size - p1) * invdir;
    ASSERT_FLOAT_EQ(far.x(), 3);
    ASSERT_FLOAT_EQ(far.y(), 5);

    auto nx = p1 + near.x() * raydir;
    auto ny = p1 + near.y() * raydir;
    ASSERT_EQ(nx, (Vector2f{3,2}));
    ASSERT_EQ(ny, (Vector2f{5,4}));

    auto fx = p1 + far.x() * raydir;
    auto fy = p1 + far.y() * raydir;
    ASSERT_EQ(fx, (Vector2f{4,3}));
    ASSERT_EQ(fy, (Vector2f{6,5}));

}