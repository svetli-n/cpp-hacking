#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief A class for reading and parsing CSV (Comma-Separated Values) files
 * 
 * The CSVReader class provides functionality to read CSV files with support for:
 * - Headers and header-less files
 * - Custom delimiters (comma, semicolon, tab, etc.)
 * - Quoted fields containing delimiters
 * - Column extraction by index or name
 * 
 * @example
 * CSVReader reader;
 * auto data = reader.readCSVWithHeaders("data.csv");
 * auto names = reader.getColumnByName(data, "Name");
 */
class CSVReader {
public:
    /**
     * @brief Constructs a CSVReader with optional delimiter specification
     * 
     * @param delimiter The character to use as field delimiter (default: comma)
     * 
     * @example
     * CSVReader reader(',');      // Comma-separated
     * CSVReader tabReader('\t');  // Tab-separated
     */
    explicit CSVReader(char delimiter = ',');
    
    /**
     * @brief Reads a CSV file and returns all data as a 2D vector
     * 
     * This method reads the entire CSV file without treating the first line
     * as headers. All rows are returned as data.
     * 
     * @param filename Path to the CSV file to read
     * @return std::vector<std::vector<std::string>> 2D vector containing all rows and columns
     * @throws std::runtime_error If the file cannot be opened
     * 
     * @example
     * CSVReader reader;
     * auto data = reader.readCSV("data.csv");
     * for (const auto& row : data) {
     *     for (const auto& cell : row) {
     *         std::cout << cell << " ";
     *     }
     * }
     */
    std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    
    /**
     * @brief Structure to hold CSV data with separate headers and rows
     * 
     * This struct separates the header row from the data rows for easier
     * column-based access and manipulation.
     */
    struct CSVData {
        std::vector<std::string> headers;  ///< Column headers from first row
        std::vector<std::vector<std::string>> rows;  ///< Data rows (excluding header)
    };
    
    /**
     * @brief Reads a CSV file treating the first line as headers
     * 
     * This method separates the first line (headers) from the rest of the data,
     * making it easier to access columns by name.
     * 
     * @param filename Path to the CSV file to read
     * @return CSVData Structure containing headers and data rows separately
     * @throws std::runtime_error If the file cannot be opened
     * 
     * @example
     * CSVReader reader;
     * auto data = reader.readCSVWithHeaders("employees.csv");
     * std::cout << "Columns: " << data.headers.size() << std::endl;
     * std::cout << "Rows: " << data.rows.size() << std::endl;
     */
    CSVData readCSVWithHeaders(const std::string& filename);
    
    /**
     * @brief Extracts a specific column from the data by its index
     * 
     * @param data The 2D vector of CSV data
     * @param columnIndex Zero-based index of the column to extract
     * @return std::vector<std::string> Vector containing all values from the specified column
     * 
     * @note If a row has fewer columns than columnIndex, an empty string is returned for that row
     * 
     * @example
     * auto data = reader.readCSV("data.csv");
     * auto firstColumn = reader.getColumn(data, 0);
     */
    std::vector<std::string> getColumn(const std::vector<std::vector<std::string>>& data, size_t columnIndex);
    
    /**
     * @brief Extracts a specific column by its header name
     * 
     * This method finds the column with the specified header name and returns
     * all values from that column.
     * 
     * @param data CSVData structure with headers
     * @param columnName Name of the column header to extract
     * @return std::vector<std::string> Vector containing all values from the specified column
     * @throws std::runtime_error If the column name is not found in headers
     * 
     * @example
     * auto data = reader.readCSVWithHeaders("employees.csv");
     * auto names = reader.getColumnByName(data, "Name");
     * auto salaries = reader.getColumnByName(data, "Salary");
     */
    std::vector<std::string> getColumnByName(const CSVData& data, const std::string& columnName);
    
    /**
     * @brief Changes the delimiter character used for parsing
     * 
     * @param delimiter The new delimiter character (e.g., ',', ';', '\t')
     * 
     * @example
     * CSVReader reader;
     * reader.setDelimiter(';');  // Switch to semicolon-separated
     * reader.setDelimiter('\t'); // Switch to tab-separated
     */
    void setDelimiter(char delimiter);
    
private:
    char delimiter_;  ///< The delimiter character used for parsing
    
    /**
     * @brief Parses a single CSV line into individual fields
     * 
     * Handles quoted fields and embedded delimiters correctly.
     * 
     * @param line A single line from the CSV file
     * @return std::vector<std::string> Vector of parsed fields
     */
    std::vector<std::string> parseLine(const std::string& line);
    
    /**
     * @brief Removes leading and trailing whitespace from a string
     * 
     * @param str String to trim
     * @return std::string Trimmed string
     */
    std::string trim(const std::string& str);
};

#endif // CSV_READER_H


