# C++ Hacking Project

A simple C++ project implementing a custom Vector class (dynamic array).

## Project Structure

```
cplusplushacking/
├── vector.h       # Vector class header
├── vector.cpp     # Vector class implementation
├── main.cpp       # Main program
├── CMakeLists.txt # CMake build configuration
└── build/         # Build directory
    └── main       # Compiled executable
```

## Features

- Custom `Vector` class implementation
- Dynamic array that grows automatically
- Methods: `push_back()`, `get()`, `size()`, `empty()`, `clear()`

## Building the Project

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher

### Build Instructions

#### On macOS/Linux:

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the program
./main
```

#### On Windows (Visual Studio):

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build . --config Release

# Run
Release\main.exe
```

## Quick Rebuild

```bash
cd build && make && ./main
```

## Example Output

```
Pushing values to vector...
Vector size: 10
Vector contents: 10 20 30 40 50 60 70 80 90 100
```

## Implementation Details

The `Vector` class demonstrates:
- Dynamic memory allocation
- Automatic resizing (doubles capacity when full)
- RAII (Resource Acquisition Is Initialization)
- Basic error handling with exceptions

Happy coding! 🚀
