cmake_minimum_required(VERSION 3.10)
project(cplusplushacking)

set(CMAKE_CXX_STANDARD 17)

# Find Catch2
find_package(Catch2 3 REQUIRED)

# Build main executable
add_executable(main main.cpp)

# Build test executable with Catch2
add_executable(test_smart_ptr test_smart_ptr.cpp)

# Link Catch2WithMain to test executable (provides main function)
target_link_libraries(test_smart_ptr Catch2::Catch2WithMain)
