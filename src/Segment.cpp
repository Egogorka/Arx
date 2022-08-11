//
// Created by Meevere on 10.08.2022.
//

#include "Segment.h"

Segment::Segment(const ndArray<Tiles, 2> &array)
:tiles(array){}

Segment::Segment(ndArray<Tiles, 2> &&array)
:tiles(std::move(array)){}
