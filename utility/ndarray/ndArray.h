//
// Created by Meevere on 07.08.2022.
//

#ifndef ARX_UTILITY_NDARRAY_NDARRAY_H
#define ARX_UTILITY_NDARRAY_NDARRAY_H

#include "ndArrayBase.h"

template<typename T, size_t N>
class ndArrayView;

#include "ndArrayView.h"

template<typename T, size_t N>
class ndArray : public ndArrayBase<T,N> {
public:
    // Rule of five constructors
    explicit ndArray(const ndArrayBase<T,N>& array)
    : ndArrayBase<T,N>(array){
        auto num_elem = this->num_elem();
        this->data = new T[num_elem];
        for(int i=0; i < num_elem; i++){
            this->data[i] = array.data[i];
        }
    }

    ndArray(const ndArray& array)
    : ndArray(static_cast<ndArrayBase<T,N>>(array)) {}

    // Now we own the data and need to free it
    ~ndArray() {
        delete [] this->data;
    }

    ndArray& operator=(const ndArrayBase<T,N>& array){
        ndArray tmp{array};
        std::swap(this->size, array.size);
        std::swap(this->data, array.data);
        return *this;
    }

    ndArray& operator=(const ndArray<T,N>& array){
        *this = static_cast<ndArrayBase<T, N>>(array);
        return *this;
    }

    //Useful constructors
    ndArray(T* data, const std::array<int,N>& size)
    : ndArray(ndArrayView<T,N>(data, size)){}

    explicit ndArray(const std::array<int,N>& size)
    : ndArrayBase<T,N>(size, new T[ndArrayBase<T,N>::fallprod(size,N)]){}

    ndArray(std::initializer_list<T> data, const std::array<int,N> size)
    : ndArray(size) {
        int num_elem = this->num_elem();
        auto iter = data.begin();
        for(int i=0; i < num_elem; i++){
            if(iter != data.end()) {
                this->data[i] = *iter;
                iter++;
            } else {
                this->data[i] = T{};
            }
        }
    }

//    //Section methods
//    ndArrayView<T,N-1> get_section(int index){
//        return ndArrayView<T,N-1>{};
//    }
};

#endif //ARX_UTILITY_NDARRAY_NDARRAY_H
