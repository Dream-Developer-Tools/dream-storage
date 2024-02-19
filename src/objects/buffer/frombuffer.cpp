#include "frombuffer.h"
#include "../dstorageobjects.h"


DreamStorage::List* DreamStorage::listFromBuffer(std::vector<uint_fast8_t> buffer) {
    auto* returnValue = new DreamStorage::List();
    std::vector<DreamStorage::ValueInternal> list;
    DreamStorage::ValueInternal v{};
    std::string stringValue;
    std::string numberValue;
    std::vector<uint_fast8_t> listValue;
    std::vector<uint_fast8_t> objectValue;
    bool boolValue;

    for (uint_fast8_t byte : buffer) {
        switch (byte) {
            case static_cast<uint_fast8_t>(Token::STRING_BEGIN):
                v.type = STRING;
                break;
            case static_cast<uint_fast8_t>(Token::STRING_END):
                break;
            case static_cast<uint_fast8_t>(Token::NUMBER_BEGIN):
                v.type = INT;
                break;
            case static_cast<uint_fast8_t>(Token::NUMBER_END):
                list.push_back(v);
                break;
            case static_cast<uint_fast8_t>(Token::TRUE):
                v.type = BOOL;
                v.boolValue = true;
                list.push_back(v);
                break;
            case static_cast<uint_fast8_t>(Token::FALSE):
                v.type = BOOL;
                v.boolValue = false;
                list.push_back(v);
                break;
            case static_cast<uint_fast8_t>(Token::LIST_BEGIN):
                v.type = LIST;
                break;
            case static_cast<uint_fast8_t>(Token::LIST_END):
                list.push_back(v);
                break;
            case static_cast<uint_fast8_t>(Token::END_OF_LINE):
                if (!stringValue.empty()) {
                    v.type = STRING;
                    new (&v.stringValue) std::string(stringValue);
                } else if (!numberValue.empty()) {
                    v.type = INT;
                    v.intValue = std::stoi(numberValue);
                } else if (!listValue.empty()) {
                    v.type = LIST;
                    new (&v.listValue) std::vector<uint_fast8_t>(listValue);
                } else if (!objectValue.empty()) {
                    v.type = OBJECT;
                    new (&v.objectValue) std::vector<uint_fast8_t>(objectValue);
                }
                break;
            default:
                switch (v.type) {
                    case STRING:
                        stringValue += byte;
                        break;
                    case INT:
                        numberValue += byte;
                        break;
                    case LIST:
                        listValue.push_back(byte);
                        break;
                    case OBJECT:
                        objectValue.push_back(byte);
                        break;
                }
                break;
        }
    }
    returnValue->list = list;
    return returnValue;
}

DreamStorage::Object* DreamStorage::objectFromBuffer(std::vector<uint_fast8_t> buffer) {
    auto* file = new DreamStorage::Object();
    bool isKey = true;
    bool isString = false;
    bool isNumber = false;
    bool isBool = false;
    bool isList = false;
    bool inList = false;
    int listBrackets = 0;

    std::string key;
    std::string stringValue;
    std::string numberValue;
    std::vector<uint_fast8_t> listValue;
    bool boolValue;
    auto* value = new DreamStorage::ValueInternal();

    for (uint_fast8_t byte : buffer) {
        if (inList) {
            if (byte == static_cast<uint_fast8_t>(Token::LIST_BEGIN)) {
                listBrackets++;
            } else if (byte == static_cast<uint_fast8_t>(Token::LIST_END)) {
                listBrackets--;
                if (listBrackets == 0) {
                    inList = false;
                }
            }
            listValue.push_back(byte);
            continue;
        }


        switch (byte) {
            case static_cast<uint_fast8_t>(Token::LIST_BEGIN):
                inList = true;
                isList = true;
                listBrackets++;
                listValue.push_back(byte);
                break;
            case static_cast<uint_fast8_t>(Token::TRUE):
                isBool = true;
                boolValue = true;
                value->type = DreamStorage::BOOL;
                value->boolValue = boolValue;
                break;
            case static_cast<uint_fast8_t>(Token::FALSE):
                isBool = true;
                boolValue = false;
                value->type = DreamStorage::BOOL;
                value->boolValue = boolValue;
                break;
            case static_cast<uint_fast8_t>(Token::NUMBER_BEGIN):
                isNumber = true;
                break;
            case static_cast<uint_fast8_t>(Token::NUMBER_END):
                isNumber = false;
                break;
            case static_cast<uint_fast8_t>(Token::STRING_BEGIN):
                isString = true;
                break;
            case static_cast<uint_fast8_t>(Token::STRING_END):
                isString = false;
                break;
            case static_cast<uint_fast8_t>(Token::IS):
                isKey = false;
                break;
            case static_cast<uint_fast8_t>(Token::END_OF_LINE):
                if (!stringValue.empty()) {
                    value->type = DreamStorage::STRING;
                    new (&value->stringValue) std::string(stringValue);
                } else if (!numberValue.empty()) {
                    value->type = DreamStorage::INT;
                    value->intValue = std::stoi(numberValue);
                } else if (isBool) {
                    value->type = DreamStorage::BOOL;
                    value->boolValue = boolValue;
                } else if (isList) {
                    value->type = DreamStorage::LIST;
                    new (&value->listValue) std::vector<uint_fast8_t>(listValue);
                }
                isKey = true;
                file->valueMap[key] = value;
                value = new DreamStorage::ValueInternal();
                key.clear();
                stringValue.clear();
                numberValue.clear();
                listValue.clear();
                isBool = false;
                isNumber = false;
                isString = false;
                isList = false;
                inList = false;
                listBrackets = 0;
                break;
            default:
                if (isString) {
                    if (isKey) {
                        key += byte;
                    } else {
                        stringValue += byte;
                    }
                } else if (isNumber) {
                    numberValue += byte;
                } else if (isList) {
                    listValue.push_back(byte);
                }
                break;
        }
    }
    return file;
}