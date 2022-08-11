#include <iostream>

#include <SFML/Graphics.hpp>
#include <Drawer.h>
#include "src/App.h"

#include <cstdlib>

#include "utility/ndarray/ndArray.h"
#include "assets/segments/l.h"

int main() {

    App app{};
    app.start();

//    Drawer drawer{{500,500}};
//
//    ndArray<Tiles,2> arr{
//        {
//            Tiles::Brick, Tiles::Brick, Tiles::Brick, Tiles::Brick, Tiles::Brick,
//            Tiles::None,  Tiles::Brick, Tiles::None,  Tiles::None,  Tiles::Brick,
//            Tiles::None,  Tiles::None,  Tiles::None,  Tiles::Brick, Tiles::None,
//            Tiles::None,  Tiles::Brick, Tiles::None,  Tiles::None,  Tiles::Brick,
//            Tiles::Brick, Tiles::Brick, Tiles::Brick, Tiles::Brick, Tiles::Brick,
//        },
//        {5, 5}
//    };
//
//    drawer.drawTiles(arr);
//    drawer.display();
//
//    int ex;
//    std::cin >> ex;

    return 0;
}
