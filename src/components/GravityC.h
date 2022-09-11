//
// Created by Meevere on 11.09.2022.
//

#ifndef ARX_SRC_COMPONENTS_GRAVITYC_H
#define ARX_SRC_COMPONENTS_GRAVITYC_H

#include "utility/vector/Vector.h"

struct GravityC {
    inline static Vector3f g{0,1./128,0};
};

#endif //ARX_SRC_COMPONENTS_GRAVITYC_H
