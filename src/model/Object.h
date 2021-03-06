//
// Created by Meevere on 27.11.2021.
//

#ifndef ARX_OBJECT_H
#define ARX_OBJECT_H

/**
 * Multiple-oriented object for all needs
 * i'm kidding, sort of
 *
 * Any of model objects that are contained in `Map`/`Container` structure must
 * be derived from `Object`
 *
 * - for what reason you wonder?
 * That is because of separation of View and Model - we need to somehow pass the information to
 * view code and switch between different view classes with respect to class.
 * For example, Dwarf class must be drawn differently in various cases - if it's Sprite view,
 * the 3D view, or anything like that.
 *
 */

// for object_types
#include <string>
#include "utility/Vector.h"

class Object {
public:
    /**
     * Position of Object in container/map.
     */
    Vector3i position;

    explicit Object(const Vector3i &position);

    /**
     * Function to get the object type
     * @return
     */
    virtual std::string getObjectType();


    virtual void update();
};


#endif //ARX_OBJECT_H
