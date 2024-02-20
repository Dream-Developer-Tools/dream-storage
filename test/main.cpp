#include <dstorage.h>
#include <iostream>
#include <chrono>
#include <fstream>


#define LOOP_COUNT 10000000

int main() {
    auto* value = new DreamStorage::Object();
    auto* list = new DreamStorage::List();
    list->addValue(std::string("hello"));
    value->setListValue("list", list);
    value->setStringValue("name", "Dream");
    value->setIntValue("age", 15);
    value->setBoolValue("isCool", true);
    value->setBoolValue("isNotCool", false);
    auto* object = new DreamStorage::Object();
    object->setStringValue("name", "Dream");
    value->setObjectValue("object", object);

    // time how long it takes to write and read from a file with precision of ms
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < LOOP_COUNT; i++) {
        std::vector<uint_fast8_t> buffer = value->asBuffer();
        auto* v = new DreamStorage::Object();
        v->setFromBuffer(buffer);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to write and read from file: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return 0;
}