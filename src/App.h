//
// Created by Meevere on 11.08.2022.
//

#ifndef ARX_SRC_APP_H
#define ARX_SRC_APP_H

#include <memory>
#include "Drawer.h"

#include "utility/Eventer.h"
#include "src/Segment.h"

#include "assets/segments/l.h"

#define RESOLUTION Vector2i{1000, 680}

class App {
    std::shared_ptr<Drawer> drawer;
    Eventer<sf::Event,sf::Event::Count> eventer;

    bool is_running;

    std::shared_ptr<std::vector<Segment>> segments;

public:
    App();

    void start();
    void end();
};


#endif //ARX_SRC_APP_H
