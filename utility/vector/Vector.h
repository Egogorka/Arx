//
// Created by Meevere on 23.10.2021.
//

#ifndef DEFANTCE_VECTOR_H
#define DEFANTCE_VECTOR_H

#include <array>
#include <iostream>

using std::array;

template<typename T, size_t N, class Derived>
class VectorBase: public array<T,N> {
    typedef const Derived& cvecr;
    typedef Derived& vecr;
public:
    static VectorBase all(T a){
        VectorBase out;
        for(auto& elem : out ){
            elem = a;
        }
        return out;
    }

    T square() const{
        T out{};
        for(const auto& elem : *this){
            out += elem*elem;
        }
        return out;
    }

    vecr operator+=(cvecr other){
        for(unsigned i=0; i<N; i++)
            this->at(i) += other[i];
        return *(static_cast<Derived*>(this));
    }

    vecr operator-=(cvecr other){
        for(unsigned i=0; i<N; i++)
            this->at(i) -= other[i];
        return *(static_cast<Derived*>(this));
    }

    vecr operator*=(T other){
        for(unsigned i=0; i<N; i++)
            this->at(i) *= other;
        return *(static_cast<Derived*>(this));
    }

    vecr operator/=(T other){
        for(unsigned i=0; i<N; i++)
            this->at(i) /= other;
        return *(static_cast<Derived*>(this));
    }

    friend Derived operator+(cvecr first, cvecr second){
        Derived out(first);
        out += second;
        return out;
    }

    friend Derived operator-(cvecr first, cvecr second){
        Derived out(first);
        out -= second;
        return out;
    }

    friend Derived operator*(cvecr first, T second){
        Derived out(first);
        out *= second;
        return out;
    }

    friend Derived operator*(T second, cvecr first){return first*second;}

    friend Derived operator/(cvecr first, T second){
        Derived out(first);
        out /= second;
        return out;
    }

    friend Derived operator-(cvecr vec){
        Derived out(vec);
        for(unsigned i = 0; i < N; ++i)
            out[i] = -vec[i];
        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, cvecr vec){
        for(unsigned i = 0; i < N-1; ++i)
            out << vec[i] << ' ';
        out << vec.back();
        return out;
    }
};

/**
 * Vector from linear algebra, as we know it
 *
 * @tparam T, type that Vector holds, for example Vector of floats
 *      this type must have overloaded += and other addition operations for proper function
 * @tparam N, a size of a Vector
 */
template<typename T, size_t N>
class Vector: public VectorBase<T, N, Vector<T,N>> {};

/**
 * Specialization for Vector2 -
 * sometimes do not want to know what x and y in array is
 */
template<typename T>
class Vector<T,2>: public VectorBase<T, 2, Vector<T,2>> {
public:
    T x() const {
        return this->at(0);
    }
    T y() const {
        return this->at(1);
    }

    T& x() {
        return this->at(0);
    }
    T& y() {
        return this->at(1);
    }
};

/**
 * Specialization for Vector3 -
 * sometimes do not want to know what x, y and z in array is
 */
template<typename T>
class Vector<T,3>: public VectorBase<T, 3, Vector<T,3>> {
public:
    T z() const {
        return this->at(0);
    }
    T x() const {
        return this->at(1);
    }
    T y() const {
        return this->at(2);
    }

    T& z() {
        return this->at(0);
    }
    T& x() {
        return this->at(1);
    }
    T& y() {
        return this->at(2);
    }

    Vector<T,2> getXY() const{
        return Vector<T,2>{this->x(), this->y()};
    }
};

typedef Vector<float,2> Vector2f;
typedef Vector<float,3> Vector3f;
typedef Vector<int,2> Vector2i;
typedef Vector<int,3> Vector3i;

Vector2f get_vector_i2f(Vector2i vec);
Vector3f get_vector_i2f(Vector3i vec);

Vector2i get_vector_f2i(Vector2f vec);
Vector3i get_vector_f2i(Vector3i vec);

template<typename T, size_t N>
Vector<T,N> get_subvector(Vector<T,N+1> vector, int index){
    Vector<T,N> out;
    int i = 0;
    for(auto& item : out){
        if(i == index) ++i;
        item = vector[i];
        ++i;
    }
    return out;
}

#endif //DEFANTCE_VECTOR_H
