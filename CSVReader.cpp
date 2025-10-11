#include "CSVReader.h"
#include <algorithm>

CSVReader::CSVReader(char delimiter) : delimiter_(delimiter) {}

std::vector<std::vector<std::string>> CSVReader::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            data.push_back(parseLine(line));
        }
    }
    
    file.close();
    return data;
}

CSVReader::CSVData CSVReader::readCSVWithHeaders(const std::string& filename) {
    CSVData result;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    
    // Read header line
    if (std::getline(file, line)) {
        result.headers = parseLine(line);
    }
    
    // Read data lines
    while (std::getline(file, line)) {
        if (!line.empty()) {
            result.rows.push_back(parseLine(line));
        }
    }
    
    file.close();
    return result;
}

std::vector<std::string> CSVReader::getColumn(const std::vector<std::vector<std::string>>& data, size_t columnIndex) {
    std::vector<std::string> column;
    
    for (const auto& row : data) {
        if (columnIndex < row.size()) {
            column.push_back(row[columnIndex]);
        } else {
            column.push_back("");
        }
    }
    
    return column;
}

std::vector<std::string> CSVReader::getColumnByName(const CSVData& data, const std::string& columnName) {
    // Find column index by name
    auto it = std::find(data.headers.begin(), data.headers.end(), columnName);
    
    if (it == data.headers.end()) {
        throw std::runtime_error("Column not found: " + columnName);
    }
    
    size_t columnIndex = std::distance(data.headers.begin(), it);
    return getColumn(data.rows, columnIndex);
}

void CSVReader::setDelimiter(char delimiter) {
    delimiter_ = delimiter;
}

std::vector<std::string> CSVReader::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == delimiter_ && !inQuotes) {
            fields.push_back(trim(field));
            field.clear();
        } else {
            field += c;
        }
    }
    
    // Add the last field
    fields.push_back(trim(field));
    
    return fields;
}

std::string CSVReader::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}


