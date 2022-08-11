//
// Created by Meevere on 11.08.2022.
//

#ifndef ARX_UTILITY_EVENTER_H
#define ARX_UTILITY_EVENTER_H

#include <list>
#include <array>
#include <functional>


/**
 * From this class I want these two behaviours
 *
 * First: adding event handlers
 * Eventer<sf::Event, sf::Event::EventType::Count> eventer;
 * eventer.add_event_listener(sf::Event::EventType::Closed
 *
 */


/**
 *
 * @tparam Event - must be a class that corresponds to events
 *      must have as a inside thing - enum EventType
 * @tparam Count - amount of the events
 */
template<typename Event, int Count>
class Eventer {
    typedef typename Event::EventType EventType; // it's enum

    /**
     * Array of lists that correspond to each type of event
     * Usage of list is justified by fast insert and linear delete
     */
    std::array<
            std::list<std::function<void(const Event&)>>
            , Count> event_listeners{};

public:
    int add_event_listener(EventType type, const std::function<void(const Event&)>& func){
        auto& list = event_listeners[static_cast<int>(type)];
        list.push_back(func);
        return list.size() - 1;
    }

    int add_event_listener(EventType type, const std::function<void()>& func){
        return add_event_listener(type, [func](const Event& e){
            func();
        });
    }

    bool remove_event_listener(EventType type, int id){
        auto list = event_listeners[static_cast<int>(type)];

        if(id >= list.size())
            return false;

        auto iter = list.begin();
        while(id --> 0) // we cant just add integers to iterators
            iter++;
        list.erase(iter);

        return true;
    }

    void evoke(const Event& event){
        for( auto& listener : event_listeners[static_cast<int>(event.type)] )
            listener(event);
    }

};

#endif //ARX_UTILITY_EVENTER_H
