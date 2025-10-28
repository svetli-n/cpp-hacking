# C++ Hacking Project

A C++ project implementing custom smart pointers: `UniquePointer` and `SharedPointer` with comprehensive tests.

## Project Structure

```
cplusplushacking/
├── smart_ptr.h        # Smart pointer implementations (UniquePointer, SharedPointer)
├── test_smart_ptr.cpp # Comprehensive Catch2 tests
├── main.cpp           # Demo program
├── CMakeLists.txt     # CMake build configuration
└── build/             # Build directory
    ├── main           # Compiled demo executable
    └── test_smart_ptr # Compiled test executable
```

## Features

- **UniquePointer**: Move-only smart pointer with custom deleters
  - Move semantics (no copying)
  - RAII (Resource Acquisition Is Initialization)
  - Custom deleter support
  - Similar to `std::unique_ptr`

- **SharedPointer**: Reference-counted smart pointer
  - Copy semantics
  - Automatic reference counting
  - Shared ownership model
  - Similar to `std::shared_ptr`

- **Testing**: Comprehensive Catch2 test suite
  - 15 test cases
  - 42+ assertions
  - Covers all functionality

## Building the Project

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher
- Catch2 installed (via Homebrew on macOS: `brew install catch2`)

### Build Instructions

#### On macOS/Linux:

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run demo program
./main

# Run tests
./test_smart_ptr
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
Release\test_smart_ptr.exe
```

## Quick Rebuild

```bash
cd build && make && ./main
cd build && make && ./test_smart_ptr
```

## Running Tests

```bash
# Run all tests
./test_smart_ptr

# Run specific test tags
./test_smart_ptr [unique_ptr]
./test_smart_ptr [shared_ptr]

# List all tests
./test_smart_ptr --list-tests
```

## Example Output

### Demo Program:
```
constructor
sv
constructor with deleter
shared constructed with deleter
custom deleter called
all shared destructed
shared destructed
custom deleter called
destructor
destructor
```

### Test Suite:
```
===============================================================================
All tests passed (42 assertions in 15 test cases)
```

## Implementation Details

The smart pointer implementations demonstrate:

### UniquePointer
- RAII (Resource Acquisition Is Initialization)
- Move semantics (no copy constructor)
- Operator overloading (`operator*`, `operator->`)
- Custom deleters
- Perfect forwarding with variadic templates

### SharedPointer
- Reference counting
- Copy semantics
- Shared ownership
- Automatic cleanup when last reference is destroyed
- Custom deleter support

## Key Concepts Used

- **RAII**: Automatic resource cleanup in destructors
- **Move semantics**: Efficient transfer of ownership
- **Reference counting**: Multiple pointers sharing the same object
- **Variadic templates**: Flexible constructors (`Args&&...`)
- **Perfect forwarding**: `std::forward` for optimal parameter passing
- **Operator overloading**: `*` and `->` for pointer-like behavior

Happy coding! 🚀
