# C++ CSV Reader Project

A modern, lightweight C++ library for reading and parsing CSV files with support for headers, quoted fields, and custom delimiters.

## Features

- 📁 Read CSV files with or without headers
- 🔍 Extract specific columns by index or name
- ✨ Handle quoted fields with commas
- ⚙️ Support for custom delimiters
- 🛡️ Error handling and validation
- 🎯 Clean, modern C++17 code

## Project Structure

```
.
├── CSVReader.h        # CSV reader class header
├── CSVReader.cpp      # CSV reader implementation
├── main.cpp           # Example usage and demo
├── sample.csv         # Sample CSV file for testing
├── CMakeLists.txt     # CMake build configuration
└── README.md          # This file
```

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
cmake --build .

# Run the program
./csv_reader

# Or with a custom CSV file
./csv_reader path/to/your/file.csv
```

#### On Windows (Visual Studio):

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build . --config Release

# Run
Release\csv_reader.exe
```

## Usage Examples

### Basic Usage

```cpp
#include "CSVReader.h"

int main() {
    CSVReader reader;
    
    // Read CSV with headers
    auto data = reader.readCSVWithHeaders("sample.csv");
    
    // Access headers
    for (const auto& header : data.headers) {
        std::cout << header << " ";
    }
    
    // Access rows
    for (const auto& row : data.rows) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
```

### Reading Without Headers

```cpp
CSVReader reader;
auto data = reader.readCSV("file.csv");

// data is a vector of vectors
for (const auto& row : data) {
    // Process each row
}
```

### Getting Specific Columns

```cpp
CSVReader reader;
auto csvData = reader.readCSVWithHeaders("sample.csv");

// Get column by name
auto names = reader.getColumnByName(csvData, "Name");

// Get column by index
auto ages = reader.getColumn(csvData.rows, 1);
```

### Using Custom Delimiters

```cpp
CSVReader reader(';'); // Use semicolon as delimiter

// Or change it later
reader.setDelimiter('\t'); // Tab-separated values
```

## API Reference

### CSVReader Class

#### Constructor
- `CSVReader(char delimiter = ',')` - Create reader with optional delimiter

#### Methods
- `readCSV(filename)` - Read CSV file, returns 2D vector of strings
- `readCSVWithHeaders(filename)` - Read CSV with headers, returns CSVData struct
- `getColumn(data, columnIndex)` - Extract column by index
- `getColumnByName(data, columnName)` - Extract column by header name
- `setDelimiter(delimiter)` - Change the delimiter character

#### CSVData Structure
```cpp
struct CSVData {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;
};
```

## Sample Output

When running with the included `sample.csv`:

```
Reading CSV file: sample.csv

=== CSV Data with Headers ===
           Name |            Age |           City |     Occupation |         Salary
------------------------------------------------------------------------------
       John Doe |             28 |       New York | Software Engineer |          95000
     Jane Smith |             32 |  San Francisco |  Data Scientist |         110000
    Bob Johnson |             45 |        Chicago | Project Manager |          85000
Alice Williams |             26 |         Boston |    UX Designer |          75000
 Charlie Brown |             38 |        Seattle | DevOps Engineer |         105000
  Diana Prince |             29 |         Austin | Product Manager |          90000
```

## Error Handling

The library throws `std::runtime_error` exceptions for:
- File not found or cannot be opened
- Column name not found (when using `getColumnByName`)

Always wrap CSV operations in try-catch blocks:

```cpp
try {
    CSVReader reader;
    auto data = reader.readCSVWithHeaders("file.csv");
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## Features Supported

✅ Comma-separated values  
✅ Custom delimiters (semicolon, tab, etc.)  
✅ Quoted fields with embedded commas  
✅ Whitespace trimming  
✅ Header row support  
✅ Column extraction by name or index  
✅ Empty line handling  

## License

This project is provided as-is for educational and commercial use.

## Contributing

Feel free to extend this library with additional features such as:
- Writing CSV files
- Type conversion utilities
- Row filtering and searching
- CSV validation
- Unicode support

Happy coding! 🚀

