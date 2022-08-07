//
// Created by Meevere on 06.08.2022.
//

#ifndef ARX_UTILITY_NDARRAY_NDARRAYBASE_H
#define ARX_UTILITY_NDARRAY_NDARRAYBASE_H

#include "vector/Vector.h"

template<typename T, size_t N>
class ndArrayBase {
public:
    T* data;
protected:
    std::array<int, N> size;

    ndArrayBase(const std::array<int,N>& size, T* data)
    :size(size), data(data){}

protected:
    ndArrayBase()
    :size(Vector<int,N>::all(1)), data{nullptr}{}

    ndArrayBase(const ndArrayBase& array) = default;
    ndArrayBase& operator=(const ndArrayBase& array) = default;

    ndArrayBase(ndArrayBase &&array) noexcept
    :size(std::move(size)), data(array.data){
        array.data = nullptr;
    }

    ndArrayBase& operator=(ndArrayBase &&array) noexcept {
        ndArrayBase tmp(std::move(array));
        std::swap(size, tmp.size);
        std::swap(data, tmp.data);
    }

public:
    virtual ~ndArrayBase() = default;

    static int fallprod(const array<int,N>& size, int pos){
        int out = 1;
        for(int i=0; i < pos; i++)
            out *= size[i];
        return out;
    }

    /*
    **
     * Converts initializer list into array of size N
     * @param list
     * @return
     *
    static std::array<int, N> from_initializer(std::initializer_list<int> list){
        std::array<int, N> temp;
        auto it = list.begin();
        for (int i = 0; i < N; ++i) {
            if( it == list.end() ) break;
            temp[i] = *it;
            ++it;
        }
        return temp;
    }
    */

    int multindex_to_index(const Vector<int, N> &multindex) const{
        int out = 0;
        for(int i=0; i < N; i++)
            out += multindex[i]*fallprod(this->size, i);
        return out;
    }

    Vector<int, N> index_to_multindex(int index) const{
        Vector<int,N> out;
        for(int i=0; i < N; i++){
            out[i] = index % this->size[i];
            index  = index / this->size[i];
        }
        return out;
    }

    [[nodiscard]] int num_elem() const{
        return fallprod(this->size, N);
    }

    std::array<int,N> get_size() const {
        return size;
    }

    // Multindex access
    T& operator[](Vector<int,N> multindex){
        return data[multindex_to_index(multindex)];
    };

    const T& operator[](Vector<int,N> multindex) const {
        return data[multindex_to_index(multindex)];
    }

    T at_def(Vector<int,N> multindex, T def) const {
        for(int i=0; i<N; i++){
            if( multindex[i] < 0 or multindex[i] > size[i] ) return def;
        }
        return (*this)[multindex];
    }

    // Iterators
    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() {return data;}
    iterator end() {return data + fallprod(size,N);}
    const_iterator cbegin() const {return data;}
    const_iterator cend() const {return data + fallprod(size,N);}
};

#endif //ARX_UTILITY_NDARRAY_NDARRAYBASE_H
