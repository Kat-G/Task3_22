#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TTable.h"
#include "TBookValue.h"

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

class CSVParser {
public:
    explicit CSVParser(const std::string& path) : m_Path(path) {}
    CSVParser(const CSVParser& p) = delete;
    CSVParser& operator=(const CSVParser& p) = delete;

    bool ParseAndInsert(PTTable table) {
        std::ifstream file(m_Path);
        if (!file.is_open()) {
            std::cerr << "File not found" << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            auto items = split(line, ';');
            if (items.size() < 2) {
                std::cerr << "File format error" << std::endl;
                return false;
            }

            TKey key = items[0];

            PTDataValue value = nullptr;

         
           
            
            value = new TBookValue(items[1],items[2]);
           

            table->InsRecord(key, value);
            //delete value;

            if (table->GetRetCode() == TabFull) {
                std::cerr << "Table is Full" << std::endl;
                return false;
            }
        }

        return true;
    }
private:
    std::string m_Path;
};