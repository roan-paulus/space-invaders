#include "reader.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace fs {
    std::string read_to_string(std::string path) {
        std::ifstream file { path };
        if (!file) {
            std::cerr << "Uh oh, " << path << " could not be opened for reading!\n";
            std::exit(1);
        }
        std::string content;
        for (std::string line; std::getline(file, line);) {
            content += line;
        }
        return content;
    }
}

