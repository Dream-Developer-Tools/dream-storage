#include "dstorage.h"
#include "objects/buffer/frombuffer.h"
#include "objects/buffer/tobuffer.h"
#include <fstream>


namespace DreamStorage {

    void writeToFile(Object *value, const char *filename) {
        std::vector<uint_fast8_t> buffer = objectToBuffer(value);
        // write the buffer to a file
        std::ofstream file;
        file.open(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing.");
        }
        file.write(reinterpret_cast<char *>(buffer.data()), buffer.size() * sizeof(int_fast8_t));
        file.close();
    }

    Object* readFromFile(const char *filename) {
        std::ifstream file;
        file.open(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for reading.");
        }

        // Determine the size of the file
        file.seekg(0, std::ios::end);
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint_fast8_t> buffer;
        // Read the entire file into the buffer
        buffer.resize(fileSize / sizeof(uint_fast8_t));
        file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

        file.close();
        return objectFromBuffer(buffer);
    }
}