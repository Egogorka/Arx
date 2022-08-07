//
// Created by Meevere on 07.08.2022.
//

#ifndef ARX_UTILITY_NDARRAY_NDARRAYVIEW_H
#define ARX_UTILITY_NDARRAY_NDARRAYVIEW_H

#include "ndArrayBase.h"

template<typename T, size_t N>
class ndArrayView : public ndArrayBase<T,N> {
public:
    // Rule of five constructors
    explicit ndArrayView(const ndArrayBase<T,N>& array)
    : ndArrayBase<T,N>(array){}

    ndArrayView(const ndArrayView& array) = default;

    // Because it's only a view and does not own the data, it doesn't need to free the data
    ~ndArrayView() = default;

    // Assignment copy
    ndArrayView& operator=(const ndArrayBase<T,N>& array){
        ndArrayView tmp{array};
        std::swap(this->size, tmp.size);
        std::swap(this->data, tmp.data);
        return *this;
    };

    ndArrayView& operator=(const ndArrayView<T,N>& array) = default;

    // Useful constructors
    ndArrayView(T* data, const std::array<int,N>& size)
    : ndArrayBase<T,N>(size, data){}


};

#endif //ARX_UTILITY_NDARRAY_NDARRAYVIEW_H
