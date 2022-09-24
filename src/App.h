//
// Created by Meevere on 11.08.2022.
//

#ifndef ARX_SRC_APP_H
#define ARX_SRC_APP_H

#include "main.h"

#include <memory>
#include "Drawer.h"

#include "utility/Eventer.h"
#include "src/Segment.h"

#include "assets/segments/l.h"

#include "src/systems/SpriteSystem.h"
#include "src/systems/TileSystem.h"
#include "src/systems/ControlsSystem.h"
#include "src/systems/PhysicsSystem.h"
#include "src/systems/GravitySystem.h"
#include "src/systems/CameraSystem.h"

#define RESOLUTION Vector2i{1000, 680}

class App {
    Drawer drawer;
    Eventer<sf::Event,sf::Event::Count> eventer;
    entt::registry registry;

    SpriteSystem spriteSystem;
    TileSystem tileSystem;
    ControlsSystem controlsSystem;
    PhysicsSystem physicsSystem;
    GravitySystem gravitySystem;
    CameraSystem cameraSystem;

    bool is_running;

    std::shared_ptr<std::vector<Segment>> segments;

public:
    App();

    void start();
    void end();
};


#endif //ARX_SRC_APP_H
