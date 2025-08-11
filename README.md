# SimpleVector

A **lightweight, educational** implementation of a dynamic array class, inspired by the C++ Standard Library's `std::vector`.  
This project is **not** a full-featured replacement for `std::vector`; it was written primarily as a learning exercise in:

- **The Rule of Five** (constructor, destructor, copy/move constructors, copy/move assignment)
- **Iterators**
- **Operator overloading**
- Basic dynamic array growth strategies

## Build & Run Instructions

This project uses **CMake** for building and includes both benchmarks and tests.

### 1. Build the Project
```bash
cmake -S . -B build
cmake --build build
```
2. Run Benchmarks

C++ benchmark:
```bash
./build/bin/vector_main
```
Python benchmark:
```bash
cd build
make python_benchmark
```
3. Run Tests
```bash
cd build
ctest
```
OR
```bash
./build/bin/vector_tests
```

## About This Project

This class is essentially a subset of what a real std::vector provides. It implements the core mechanics for pushing, popping, reserving, and iterating, but omits advanced features like:
	•	Custom allocators
	•	Exception safety guarantees for all operations
	•	Debug iterator safety checks
	•	Full conformance to every edge case in the C++ standard

The goal was education, not to outdo the standard library.

## Benchmark Observation

In a simple benchmark pushing back one million `std::string` objects, this implementation ran **5-6x as fast** as `std::vector` when compiled with `g++` under the tested conditions.

**Average Implementation Speeds**

| Implementation  | Time (ms) |
|-----------------|-----------|
| VectorLite      | 3.5       |
| std::vector     | 20        |
| Python list     | 45        |

This was unexpected. The primary suspects for the performance I have come up with are:

- **Simplicity**:  
  The implementation is minimal compared to std::vector; for instance it lacks an allocator object or type trait machinery.
- **Fewer safety checks**:  
  The standard library adds layers for type safety. Both push_back and emplace_back have strong expection guarantees, which can cost performance in microbenchmarks.
  source: https://en.cppreference.com/w/cpp/container/vector.html
