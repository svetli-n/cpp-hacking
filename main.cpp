#include <iostream>
#include <iomanip>
#include "CSVReader.h"

void printTable(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << std::setw(15) << row[i];
            if (i < row.size() - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }
}

void printWithHeaders(const CSVReader::CSVData& data) {
    // Print headers
    std::cout << "\n=== CSV Data with Headers ===\n";
    for (size_t i = 0; i < data.headers.size(); ++i) {
        std::cout << std::setw(15) << data.headers[i];
        if (i < data.headers.size() - 1) {
            std::cout << " | ";
        }
    }
    std::cout << "\n";
    std::cout << std::string(data.headers.size() * 18, '-') << "\n";
    
    // Print rows
    printTable(data.rows);
}

int main(int argc, char* argv[]) {
    try {
        std::string filename = "sample.csv";
        
        // Allow user to specify file via command line
        if (argc > 1) {
            filename = argv[1];
        }
        
        std::cout << "📄 Reading CSV file: " << filename << std::endl;
        
        // Create CSV reader
        CSVReader reader;
        
        // Example 1: Read CSV with headers
        std::cout << "\n--- Example 1: Reading CSV with headers ---\n";
        auto csvData = reader.readCSVWithHeaders(filename);
        printWithHeaders(csvData);
        
        // Example 2: Get specific column by name
        std::cout << "\n--- Example 2: Get specific column by name ---\n";
        if (!csvData.headers.empty()) {
            std::string columnName = csvData.headers[0];
            std::cout << "Column '" << columnName << "':\n";
            auto column = reader.getColumnByName(csvData, columnName);
            for (const auto& value : column) {
                std::cout << "  - " << value << std::endl;
            }
        }
        
        // Example 3: Get column by index
        std::cout << "\n--- Example 3: Get column by index ---\n";
        if (!csvData.rows.empty() && csvData.rows[0].size() > 1) {
            auto column = reader.getColumn(csvData.rows, 1);
            std::cout << "Column at index 1:\n";
            for (const auto& value : column) {
                std::cout << "  - " << value << std::endl;
            }
        }
        
        // Example 4: Statistics
        std::cout << "\n--- Example 4: Statistics ---\n";
        std::cout << "Number of rows: " << csvData.rows.size() << std::endl;
        std::cout << "Number of columns: " << csvData.headers.size() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

