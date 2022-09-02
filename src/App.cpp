//
// Created by Meevere on 11.08.2022.
//

#include "App.h"

#include "src/components/LocationC.h"

App::App()
: is_running(false), spriteSystem(), tileSystem(){
    drawer = std::make_shared<Drawer>(RESOLUTION);
    segments = load_segments();

    eventer.add_event_listener(sf::Event::EventType::Closed, [this](){
        this->end();
    });

    eventer.add_event_listener(sf::Event::EventType::KeyPressed,
       [this](const sf::Event& event){
           switch (event.key.code) {
               case sf::Keyboard::Comma: // <
                   drawer->parallax_scale /= 1.1;
                   break;
               case sf::Keyboard::Period: // >
                   drawer->parallax_scale *= 1.1;
                   break;
               case sf::Keyboard::Up:
                   drawer->parallax_center += Vector2f{0,.1};
                   break;
               case sf::Keyboard::Down:
                   drawer->parallax_center += Vector2f{0,-.1};
                   break;
               case sf::Keyboard::Left:
                   drawer->parallax_center += Vector2f{-.1,0};
                   break;
               case sf::Keyboard::Right:
                   drawer->parallax_center += Vector2f{.1,0};
                   break;
               case sf::Keyboard::PageUp:
                   drawer->parallax_offset += .1;
                   break;
               case sf::Keyboard::PageDown:
                   drawer->parallax_offset += -.1;
                   break;
               case sf::Keyboard::Enter:
                   std::cout << "Current parallax settings\n";
                   std::cout << "Parallax offset: " << drawer->parallax_offset << '\n';
                   std::cout << "Parallax scale:  " << drawer->parallax_scale << '\n';
                   std::cout << "Parallax center: " << drawer->parallax_center << '\n';
                   break;

               default:
                   break;
           }
       });
}

void App::start() {
    is_running = true;

    auto player = registry.create();

    registry.emplace<LocationC>(player, Vector3f{1,1,1});
    spriteSystem.assign(registry, player, Sprites::Player);

//    eventer.add_event_listener(sf::Event::EventType::KeyPressed,
//       [this, &player_pos](const sf::Event& event){
//           switch (event.key.code) {
//               case sf::Keyboard::W:
//                   player_pos.y() += -.1;
//                   break;
//               case sf::Keyboard::A:
//                   player_pos.x() += -.1;
//                   break;
//               case sf::Keyboard::D:
//                   player_pos.x() += .1;
//                   break;
//               case sf::Keyboard::S:
//                   player_pos.y() += .1;
//                   break;
//
//               default:
//                   break;
//           }
//    });

    int counter = 0;
    sf::Clock clock;
    while (is_running) {
        sf::Event event{};
        drawer->clear();

//        drawer->drawTiles(segments->at(0).tiles, 3);
//        drawer->drawTiles(segments->at(0).tiles, 2);

//        drawer->drawTiles(segments->at(0).tiles, 1);
//        drawer->drawMSprite(0,Vector3f{8,2,1},1, abs(counter - 6));
//        drawer->drawMSprite(1,player_pos,0,counter % 4);
//
//        drawer->drawTiles(segments->at(0).tiles);
//        drawer->drawMSprite(0,Vector3f{2,2,0},0, abs(counter - 6));

        auto time = clock.restart();
        spriteSystem.render(registry, *drawer, time);
        drawer->display_sprites([this](int zlevel){
            this->tileSystem.render_partial(this->segments->at(0).tiles, zlevel, *drawer);
        }, 3);

        while (drawer->pollEvent(event)){
            eventer.evoke(event);
        }

        drawer->display();

    }
}


void App::end() {
    is_running = false;
}
