#include "Vector.h"
#include <cassert>
#include <iostream>
#include <string>

struct Test
{
void TestBasicConstruction()
{
    //Tests Default Construction and Overloaded Construction
    Vector<int> a; 
    Vector<double> g(static_cast<size_t>(8)); 
    Vector<int> arrvec({4, 5, 6, 9});

    a.print();
    g.print();
    arrvec.print();
}

void TestCopyConstruction()
{
    Vector<int> first({1, 2, 3, 4});
    Vector<int> copy = first; 
    assert(first[2] == copy[2]);
    first[2] = 8;
    assert(first[2] != copy[2]);
}

void TestCopyAssignment()
{
    Vector<int> first({1, 2, 3, 4});
    Vector<int> copy({5, 6, 7, 8});

    copy = first;  

    assert(first[2] == copy[2]);
    first[2] = 8;
    assert(first[2] != copy[2]);

}



void TestMoveConstruction()
{
    Vector<int> a({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Vector<int> ILikeToMoveit = std::move(a);
    ILikeToMoveit.print();
}

void TestMoveAssignment()
{
    Vector<int> a({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Vector<int> ILikeToMoveit;
    ILikeToMoveit = std::move(a);
    ILikeToMoveit.print();
}

void TestPushBack()
{
    Vector<int> myVector;

    for (int i = 0; i < 1000; i++)
    {
        myVector.push_back(i);
    }
    myVector.print();
    std::cout << myVector.size() << '\n';
}

void TestAccessOperator()
{
    std::string a { "Step 1. Go to the store\n"};
    std::string b { "Step 2. Purchase Eggs, Milk, Flour and Backing Soda \n"};
    std::string c { "Step 3. Cook Pancakes\n"};

    Vector<std::string> tasks({a, b, c});

    assert(tasks[0] == a);
    assert(tasks[1] == b);
    assert(tasks[2] == c);

    //testing reassignment

    tasks[1] = "Step 2. Purchase Complete Pancake Mix";

    assert(tasks[1] != b);

    //testing const operator

    const Vector<std::string> constant_tasks({a, b, c});

    assert(constant_tasks[0] == a);
    assert(constant_tasks[1] == b);
    assert(constant_tasks[2] == c);

}


void TestBasicFunctions()
{
    //Tests .empty() .size() .capacity()


}
};

int main()
{
    Test test;
    test.TestPushBack();
}