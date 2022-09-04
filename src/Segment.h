//
// Created by Meevere on 10.08.2022.
//

#ifndef ARX_SRC_SEGMENT_H
#define ARX_SRC_SEGMENT_H

#include "utility/ndarray/ndArray.h"
#include "assets/tiles.h"

// Level segment class
struct Segment {
    ndArray<Tiles,2> tiles;


    Segment(const ndArray<Tiles,2>& array);
    Segment(ndArray<Tiles,2>&& array);
};


#endif //ARX_SRC_SEGMENT_H
