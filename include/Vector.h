#include <cstddef>
#include <ostream>

template <typename T>
class Vector
{
    public:
        Vector();
        Vector(size_t initialCapacity);
        Vector(std::initializer_list<T> list); 
        ~Vector();

        Vector(const Vector<T>& other);
        Vector(Vector<T>&& other) noexcept; //Move constructor

        Vector<T>& operator=(const Vector<T>& rhs); //Copy assign
        Vector<T>& operator=(Vector<T>&& rhs) ; //Move assign

        void push_back(const T& lvalue); // add item to end
        void push_back(const T&& rvalue); // add item to end
        void pop_back();

        void pop(); // Exception Defined version of pop_back


        T& at(size_t index); //safer implementation of operator[] throws std::out_of_range if out of bounds

        T& operator[](size_t index);
        const T& operator[](size_t index) const; //access

        size_t size() const; // current number of element

        size_t capacity() const; 

        bool empty() const;

        void clear();

        bool operator==(const Vector<T>& rhs) const;
        bool operator!=(const Vector<T>& rhs) const;

        void print();

    private:

        static constexpr size_t default_capacity = 4; 

        T* data;
        size_t sz;
        size_t cap;
        
        void destroy();
        void double_capacity();
        void copyFrom(const Vector<T>& other);
        void resize();
        void swap(Vector<T>& vec1, Vector<T>& vec2);
};