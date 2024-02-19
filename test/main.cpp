#include <dstorage.h>
#include <iostream>

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

    DreamStorage::writeToFile(value, "test.txt");
    DreamStorage::Object* readValue = DreamStorage::readFromFile("test.txt");
    std::cout << readValue->getValue("name")->stringValue << std::endl;
    std::cout << readValue->getValue("list")->listValue->list[0].stringValue << std::endl;
    return 0;
}