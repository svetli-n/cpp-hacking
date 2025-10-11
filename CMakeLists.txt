cmake_minimum_required(VERSION 3.10)
project(CSVReader VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Create the executable
add_executable(csv_reader
    main.cpp
    CSVReader.cpp
)

# Include directories
target_include_directories(csv_reader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


