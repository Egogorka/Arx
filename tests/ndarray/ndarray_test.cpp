//
// Created by Meevere on 07.08.2022.
//


#include "utility/ndarray/ndArray.h"

#include <gtest/gtest.h>

TEST(ndArray_test, construction){
    // usual constructor;
    ndArray<int, 3> array1{{3, 2, 2}}; // 3*2*2 = 12

    int data[] = {
            1, 2,   3, 4,
            5, 6,   7, 8,
            9,10,  11,12
    };

    // with array
    auto array2 = ndArray<int, 3>(data, Vector3i{3,2,2});

    // with initializer-list
    auto array3 = ndArray<int, 3>(data, {3,2,2});

    // from list
    auto array4 =
            ndArray<int, 3>(
                    {
                            1, 2,   3, 4,
                            5, 6,   7, 8,
                            9,10,  11,12
                    }, {3,2,2}
            );

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                ASSERT_EQ((array2[Vector3i{i,j,k}]), array1.multindex_to_index(Vector3i{i,j,k})+1);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                ASSERT_EQ((array3[Vector3i{i,j,k}]), array1.multindex_to_index(Vector3i{i,j,k})+1);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                ASSERT_EQ((array4[Vector3i{i,j,k}]), array1.multindex_to_index(Vector3i{i,j,k})+1);
            }
        }
    }
}

TEST(ndArray_test, access){
    ndArray<int, 3> array1{{4, 3, 2}};

    EXPECT_EQ((array1.get_size()), (Vector3i{4,3,2}));

    int counter = 0;
    for (auto &item : array1) {
        item = counter;
        counter++;
    }

    counter = 0;
    for (auto &item : array1) {
        EXPECT_EQ(item, counter);
        counter++;
    }

    EXPECT_EQ((array1[Vector3i{3,0,0}]), array1.multindex_to_index(Vector3i{3,0,0}));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 2; ++k) {
                EXPECT_EQ((array1[Vector3i{i,j,k}]), array1.multindex_to_index(Vector3i{i,j,k}));
            }
        }
    }

    EXPECT_EQ((array1.at_def(Vector3i{4,4,4}, 42)),42);
    EXPECT_EQ((array1.at_def(Vector3i{0,0,0}, 42)),0);
}
//
//TEST(ndArray_test, array_functions){
//    auto arr = ndArray<int,2>::from_data(
//            {
//                    0,0,0,0,0,
//                    0,2,2,2,0,
//                    0,2,2,2,0,
//                    0,2,2,2,0,
//                    0,0,0,0,0,
//            }, {5,5});
//
//    auto grad_sq = find_boundaries(arr, std::function{[](int a){return a > 0 ? 1 : 0;}});
//
//    EXPECT_EQ(get_gradient_at(arr, Vector2i{1,1}), (Vector2i{1,1}));
//    EXPECT_EQ(get_gradient_at(arr, Vector2i{1,4}), (Vector2i{0,-1}));
//
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            std::cout << grad_sq[Vector2i{i,j}] << ' ';
//        }
//        std::cout << '\n';
//    }
//}
//
//TEST(ndArray_test, array_functions_boundary){
//    auto arr = ndArray<int,2>::from_data(
//            {
//                    0,0,0,0,0,
//                    0,2,2,2,0,
//                    0,2,0,2,0,
//                    0,2,2,2,0,
//                    0,0,0,0,0,
//            }, {5,5});
//
//    auto boundary = find_boundaries(arr, std::function{[](int a){return a;}});
//
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            std::cout << boundary[Vector2i{i,j}] << ' ';
//        }
//        std::cout << '\n';
//    }
//}
//
//TEST(ndArray_test, equality){
//    auto arr = ndArray<int,2>::from_data(
//            {
//                    0,0,0,0,0,
//                    0,2,2,2,0,
//                    0,2,2,2,0,
//            }, {5,3});
//
//    auto arr2 = ndArray<int,2>::from_data(
//            {
//                    0,0,0,0,0,
//                    0,2,2,2,0,
//                    0,2,2,2,0,
//            }, {5,3});
//
//    auto arr3 = ndArray<int,2>::from_data(
//            {
//                    0,0,0,0,
//                    0,2,2,2,
//                    0,2,2,2,
//            }, {4,3});
//
//
//    EXPECT_EQ(arr, arr2);
//    EXPECT_EQ(arr, arr);
//    EXPECT_NE(arr3, arr2);
//}
//
//TEST(ndArray_test, get_section) {
//    auto arr = ndArray<int, 2>::from_data(
//            {
//                    0, 0, 0, 0, 0,
//                    0, 2, 2, 2, 0,
//                    0, 2, 2, 2, 0,
//                    0, 2, 2, 2, 0,
//                    0, 0, 0, 0, 0,
//            }, {5, 5});
//
//    auto arr_sect_1 = arr.get_section(0);
//    auto arr_sect_eq1 = ndArray<int, 1>::from_data(
//            {0, 0, 0, 0, 0}, {5}
//    );
//
//    auto arr_sect_2 = arr.get_section(1);
//    auto arr_sect_eq2 = ndArray<int, 1>::from_data(
//            {0, 2, 2, 2, 0}, {5}
//    );
//
//    EXPECT_EQ(arr_sect_1, arr_sect_eq1);
//    EXPECT_EQ(arr_sect_2, arr_sect_eq2);
//    EXPECT_NE(arr_sect_1, arr_sect_eq2);
//}