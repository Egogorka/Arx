//
// Created by meeve on 03.08.2022.
//

#include <nlohmann/json.hpp>
#include <gtest/gtest.h>
using json = nlohmann::json;

TEST(HelloTest, JsonTest) {
    json ex1 = json::parse(R"(
        {
            "pi": 3.141,
            "happy": true
        }
    )");

    EXPECT_EQ(ex1["pi"], 3.141);
    EXPECT_EQ(ex1["happy"], true);


}