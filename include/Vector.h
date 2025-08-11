#include <cstddef>
#include <iostream>
#include <utility>
#include <initializer_list>

template <typename T>
class VectorLite
{
    public:
        VectorLite();
        VectorLite(size_t initialCapacity);
        VectorLite(std::initializer_list<T> list); 

        /* RULE OF FIVE */
        ~VectorLite();

        VectorLite(const VectorLite<T>& other); //Copy Constructor
        VectorLite(VectorLite<T>&& other) noexcept; //Move constructor

        VectorLite<T>& operator=(const VectorLite<T>& rhs); //Copy assign
        VectorLite<T>& operator=(VectorLite<T>&& rhs) ; //Move assign

        void push_back(const T& lvalue); 
        void push_back(T&& rvalue); 
        void pop_back();

        void pop(); // Exception Defined version of pop_back


        T& at(size_t index); //safer implementation of operator[] throws std::out_of_range if out of bounds
        const T& at(size_t index) const;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        size_t size() const; 

        size_t capacity() const; 

        bool empty() const;

        void clear();

        bool operator==(const VectorLite<T>& rhs) const;
        bool operator!=(const VectorLite<T>& rhs) const;

        void print();

        friend void swap(VectorLite<T>& vec1, VectorLite<T>& vec2) noexcept
        {
            vec1.swap(vec2);
        }
    
        void reserve(size_t newCapacity);

        class iterator {
            private:
                T* ptr;
            public:
                using value_type = T;
                using difference_type = std::ptrdiff_t;
                using pointer = T*;
                using reference = T&;
                using iterator_category = std::forward_iterator_tag;
                iterator(T* p) : ptr(p) {}

                T& operator*() { return *ptr; }

                iterator& operator++() { ptr++; return *this; }
                iterator& operator--() { ptr--; return *this; }
                iterator operator++(int) { iterator old(ptr); ptr++; return old; }
                iterator operator--(int) { iterator old(ptr); ptr--; return old; }

                bool operator==(const iterator& other) const { return ptr == other.ptr; }
                bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        };

        class const_iterator {
            private:
                const T* ptr;
            public:
                using value_type = T;
                using difference_type = std::ptrdiff_t;
                using pointer = const T*;
                using reference = const T&;
                using iterator_category = std::forward_iterator_tag;
                const_iterator(const T* p) : ptr(p) {}

                const T& operator*() const { return *ptr; }
                
                const_iterator& operator++() { ptr++; return *this; }
                const_iterator& operator--() { ptr--; return *this; }
                const_iterator operator++(int) { const_iterator old(ptr); ptr++; return old; }
                const_iterator operator--(int) { const_iterator old(ptr); ptr--; return old; }


                bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
                bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
    };

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    private:

        static constexpr size_t default_capacity = 4; 

        T* data;
        size_t sz;
        size_t cap;
        
        void destroy();
        void copyFrom(const VectorLite<T>& other);
        void double_capacity();
        void swap(VectorLite<T>& other) noexcept;
};

// ============================== Definitions ==============================

template <typename T>
VectorLite<T>::VectorLite(): 
    sz { 0 }, 
    cap { default_capacity }, 
    data { new T[default_capacity] }
{ }

template <typename T>
VectorLite<T>::VectorLite(size_t initialCapacity): 
    sz { 0 }, 
    cap { initialCapacity ? initialCapacity : 1 }, 
    data { new T[initialCapacity] }
{ }

template <typename T>
VectorLite<T>::VectorLite(std::initializer_list<T> initList):
sz { 0 },
cap { 0 },
data { nullptr }
{
    VectorLite tmp;
    tmp.reserve(initList.size());
    for (const T& val : initList)
    {
        tmp.push_back(val);
    }
    swap(tmp);
}

template <typename T>
VectorLite<T>::VectorLite(const VectorLite<T>& other):
sz { 0 }, 
cap { 0 },
data { nullptr } 
{
    VectorLite tmp;
    tmp.reserve(other.size());
    for (const T& val : other)
    {
        tmp.push_back(val);
    }
    swap(tmp);
}

template <typename T>
VectorLite<T>& VectorLite<T>::operator=(const VectorLite& rhs)
{
    VectorLite<T> temp = rhs;
    swap(temp);

    return *this;
}

template <typename T>
VectorLite<T>& VectorLite<T>::operator=(VectorLite&& toMove) 
{ 
    swap(toMove);
    return *this;
}

template <typename T>
VectorLite<T>::VectorLite(VectorLite<T>&& other) noexcept:
sz { other.sz }, 
cap { other.cap },
data { other.data } 
{
    other.data = nullptr;
    other.sz = 0;
    other.cap = default_capacity;
}

template <typename T>
VectorLite<T>::~VectorLite()
{
    destroy();
}

template <typename T>
void VectorLite<T>::push_back(const T& lvalue)
{
    if (sz == cap)
        double_capacity();
    data[sz++] = lvalue;
}

template <typename T>
void VectorLite<T>::push_back(T&& rvalue)
{
    if (sz == cap)
        double_capacity();
    data[sz++] = std::move(rvalue);
}

template <typename T>
void VectorLite<T>::pop_back()
{
    sz--;
}

template <typename T>
void VectorLite<T>::pop()
{
    if(sz == 0)
        throw std::out_of_range("Attempt to pop an empty array");
    pop_back();
}



template <typename T>
T& VectorLite<T>::at(size_t index)
{
    if (index >= sz)
        throw std::out_of_range("Index out of bounds");
    return data[index];
}

template <typename T>
const T& VectorLite<T>::at(size_t index) const
{
    if (index >= sz)
        throw std::out_of_range("Index out of bounds");
    return data[index];
}

template <typename T>
T& VectorLite<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T& VectorLite<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
void VectorLite<T>::destroy()
{
    delete[] data;
    sz = 0;
    cap = default_capacity;
    data = nullptr;
}

template <typename T>
size_t VectorLite<T>::capacity() const
{
    return cap;
}

template <typename T>
size_t VectorLite<T>::size() const
{
    return sz;
}

template <typename T>
bool VectorLite<T>::empty() const
{
    return sz == static_cast<size_t>(0);
}

template <typename T>
void VectorLite<T>::double_capacity()
{
    VectorLite<T> newVectorLite(cap * 2); 
    for (size_t idx = 0; idx < sz; idx++)
    {
        newVectorLite.data[idx] = std::move_if_noexcept(data[idx]);
    }
    newVectorLite.sz = sz;
    swap(newVectorLite);
    
}

template <typename T>
void VectorLite<T>::swap(VectorLite<T>& other) noexcept
{
    using std::swap; 
    swap(cap, other.cap);
    swap(sz, other.sz);
    swap(data, other.data);
}

template <typename T>
bool VectorLite<T>::operator==(const VectorLite<T>& rhs) const
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
bool VectorLite<T>::operator!=(const VectorLite<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
void VectorLite<T>::print()
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
void VectorLite<T>::clear()
{
    destroy();
}

template <typename T>
void VectorLite<T>::reserve(size_t newCapacity)
{
    if (cap >= newCapacity)
        return;

    VectorLite<T> newVec(newCapacity);

    for (size_t idx = 0; idx < sz; idx++)
    {
        newVec[idx] = std::move_if_noexcept(data[idx]);
    }
    newVec.sz = sz;
    swap(newVec);

}

template <typename T>
typename VectorLite<T>::iterator VectorLite<T>::begin() { return iterator(data); }

template <typename T>
typename VectorLite<T>::iterator VectorLite<T>::end() { return iterator(data + sz); }

/* Read only access of const VectorLite*/
template <typename T>
typename VectorLite<T>::const_iterator VectorLite<T>::begin() const { return const_iterator(data); }

template <typename T>
typename VectorLite<T>::const_iterator VectorLite<T>::end() const { return const_iterator(data + sz); }


/* Read only access of non const and const VectorLite*/
template <typename T>
typename VectorLite<T>::const_iterator VectorLite<T>::cbegin() const { return begin(); }

template <typename T>
typename VectorLite<T>::const_iterator VectorLite<T>::cend() const { return end(); } 