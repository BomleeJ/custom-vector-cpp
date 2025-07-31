#include <cstddef>
#include "Vector.h"
#include <iostream>
#include <utility>
#include <initializer_list>


template <typename T>
Vector<T>::Vector(): 
    sz { 0 }, 
    cap { default_capacity }, 
    data { new T[default_capacity] }
{ std::cout << "Default Constructor Called \n"; }

template <typename T>
Vector<T>::Vector(size_t initialCapacity): 
    sz { 0 }, 
    cap { initialCapacity }, 
    data { new T[initialCapacity] }
{ std::cout << "Empty Initial Capacity Constructor Called \n"; }

template <typename T>
Vector<T>::Vector(std::initializer_list<T> initList):
sz { initList.size() },
cap { initList.size() * 2},
data { new T[initList.size() * 2] }
{
    const T* elem = std::move(initList.begin());
    for (size_t idx = 0; idx < sz; idx++)
    {
        data[idx] = *(elem++);
    }
    std::cout << "Array Constructor Called\n"; 
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other):
sz { other.size() }, 
cap { other.capacity() },
data { new T[other.size()] } 
{
    for (size_t i = 0; i < other.size(); i++)
    {
        data[i] = other[i];
    }
    std::cout << "Copy Constructor Called\n"; 
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    Vector<T> temp = rhs;
    swap(*this, temp);
    std::cout << "Copy Assignment Operator Called\n"; 

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& toMove) 
{ 
    swap(*this, toMove);
    std::cout << "Move Assignment Operator Called\n";
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept:
sz { other.sz }, 
cap { other.cap },
data { other.data } 
{
    other.data = nullptr;
    other.sz = 0;
    other.cap = default_capacity;

    std::cout << "Move Constructor Called\n";

}

template <typename T>
Vector<T>::~Vector()
{
    destroy();
    std::cout << "Destructor Complete \n";
}

template <typename T>
void Vector<T>::print()
{
    std::cout << "[";
    if (!empty())
    {
        for (size_t idx = 0; idx < sz - 1; idx++)
        {
            std::cout << this->at(idx) << ", ";
        }
        std::cout << this->at(sz-1);
    }
    std::cout << "]\n";
}


template <typename T>
void Vector<T>::push_back(const T& lvalue)
{
    if (sz == cap)
        resize();
    data[sz++] = lvalue;
}

template <typename T>
void Vector<T>::push_back(const T&& rvalue)
{
    if (sz == cap)
        resize();
    data[sz++] = std::move(rvalue);
}

template <typename T>
void Vector<T>::pop_back()
{
    data[(sz - 1)].~T();
    sz--;
}

template <typename T>
void Vector<T>::pop()
{
    if(sz == 0)
        throw std::out_of_range("Attempt to pop an empty array");
    pop_back();
}



template <typename T>
T& Vector<T>::at(size_t index)
{
if (index >= sz)
    throw std::out_of_range("Index out of bounds");
return data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
void Vector<T>::destroy()
{
    delete[] data;
    sz = 0;
    cap = default_capacity;
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return cap;
}

template <typename T>
size_t Vector<T>::size() const
{
    return sz;
}

template <typename T>
bool Vector<T>::empty() const
{
    return sz == static_cast<size_t>(0);
}

template <typename T>
void Vector<T>::resize()
{
    Vector<T> newVector(cap * 2); 
    for (size_t idx = 0; idx < sz; idx++)
    {
        newVector.data[idx] = data[idx];
    }
    newVector.sz = sz;
    swap(newVector, *this);
    
}

template <typename T>
void Vector<T>::swap(Vector<T>& vec1, Vector<T>& vec2)
{
    T* tempdata = vec1.data;
    size_t tempsz = vec1.sz;
    size_t tempcap = vec1.cap;

    vec1.data = vec2.data;
    vec1.sz = vec2.sz;
    vec1.cap = vec2.cap;

    vec2.data = tempdata;
    vec2.sz = tempsz;
    vec2.cap = tempcap;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& rhs) const
{
    if (sz != rhs.sz)
        return false;

    for (size_t i = 0; i < sz; i++)
    {
        if(data[i] != rhs.data[i])
            return false;
    }

    return true;

}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& rhs) const
{
    return !(*this == rhs);
}