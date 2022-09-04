//
// Created by meeve on 02.08.2022.
//

#include "l.h"
#include "assets/tiles.h"

#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <array>

std::shared_ptr<std::vector<Segment>> load_segments() {
    std::ifstream f("../assets/segments/test_seg.json");

    auto out = std::make_shared<std::vector<Segment>>();
    json array_data = json::parse(f);

    out->reserve(array_data.size());
    for(auto& data : array_data){
        auto size = data["size"].get<std::array<int,2>>();
        auto map = data["visual"]["map"].get<std::vector<std::string>>();
        auto symbols = data["visual"]["symbols"];

        std::cout << "Reading the map\n";

        ndArray<Tiles,2> temp{size};
        for(int i=0; i < size[1]; i++){ // fixate the row
            for(int j=0; j < size[0]; j++){ // fixate the column
                auto cur_tile = symbols[std::string{map[i][j]}].get<Tiles>();
                temp[Vector2i{j,i}] = cur_tile;
                std::cout << static_cast<int>(cur_tile);
            }
            std::cout << '\n';
        }
        out->emplace_back(std::move(temp));
    }

    f.close();
    return out;

}

