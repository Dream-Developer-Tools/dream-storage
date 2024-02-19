#include <algorithm>
#include "dstorageobjects.h"
#include "buffer/frombuffer.h"

namespace DreamStorage {

    Value::Value(const ValueInternal &other) : type(other.type) {
        switch (type) {
            case INT:
                new(&intValue) int(other.intValue);
                break;
            case BOOL:
                new(&boolValue) bool(other.boolValue);
                break;
            case STRING:
                new(&stringValue) std::string(other.stringValue);
                break;
            case LIST:
                listValue = new List();
                listValue->setFromBuffer(other.listValue);
                break;
            case OBJECT:
                objectValue = new Object();
                objectValue->setFromBuffer(other.objectValue);
                break;
        }
    }

    Object::Object() {
        valueMap = std::unordered_map<std::string, ValueInternal *>();
    }

    Object::~Object() {
        valueMap.clear();
    }

    void Object::setStringValue(const std::string &key, const std::string &value) {
        auto *v = new ValueInternal();
        v->type = STRING;
        new(&v->stringValue) std::string(value);
        valueMap[key] = v;
    }

    void Object::setIntValue(const std::string &key, int value) {
        auto *v = new ValueInternal();
        v->type = INT;
        new(&v->intValue) int(value);
        valueMap[key] = v;
    }

    void Object::setBoolValue(const std::string &key, bool value) {
        auto *v = new ValueInternal();
        v->type = BOOL;
        new(&v->boolValue) bool(value);
        valueMap[key] = v;
    }

    List::List() {
        list = std::vector<ValueInternal>();
    }

    Value *Object::getValue(const std::string &key) {
        auto *value = valueMap[key];
        auto *v = new Value();
        v->type = value->type;
        switch (value->type) {
            case INT:
                new(&v->intValue) int(value->intValue);
                break;
            case BOOL:
                new(&v->boolValue) bool(value->boolValue);
                break;
            case STRING:
                new(&v->stringValue) std::string(value->stringValue);
                break;
            case LIST:
                v->listValue = new List();
                v->listValue->setFromBuffer(value->listValue);
                break;
        }
        return v;
    }

    std::vector<uint_fast8_t> List::asBuffer() {
        std::vector<uint_fast8_t> buffer = std::vector<uint_fast8_t>();
        for (const ValueInternal &val: list) {
            switch (val.type) {
                case STRING:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: val.stringValue) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case INT:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::NUMBER_BEGIN));
                    for (char c: std::to_string(val.intValue)) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::NUMBER_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case BOOL:
                    if (val.boolValue) {
                        buffer.push_back(static_cast<uint_fast8_t>(Token::TRUE));
                    } else {
                        buffer.push_back(static_cast<uint_fast8_t>(Token::FALSE));
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case LIST:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::LIST_BEGIN));
                    for (uint_fast8_t byte: val.listValue) {
                        buffer.push_back(byte);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::LIST_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
            }
        }
        return buffer;
    }

    std::vector<uint_fast8_t> Object::asBuffer() {

    }

    void Object::setListValue(const std::string &key, List *value) {
        auto *v = new ValueInternal();
        v->type = LIST;
        new(&v->listValue) std::vector<uint_fast8_t>(value->asBuffer());
        valueMap[key] = v;
    }

    void Object::setObjectValue(const std::string &key, Object *value) {
        auto *v = new ValueInternal();
        v->type = OBJECT;
        new(&v->objectValue) std::vector<uint_fast8_t>(value->asBuffer());
        valueMap[key] = v;
    }

    void List::addValue(const std::string &value) {
        ValueInternal v{};
        v.type = STRING;
        new(&v.stringValue) std::string(value);
        list.push_back(v);
    }

    List::~List() {
        list.clear();
    }

    void Object::setFromBuffer(std::vector<uint_fast8_t> buffer) {
        this->valueMap = objectFromBuffer(buffer)->valueMap;
    }

    void List::setFromBuffer(std::vector<uint_fast8_t> buffer) {
        this->list = listFromBuffer(buffer)->list;
    }
}