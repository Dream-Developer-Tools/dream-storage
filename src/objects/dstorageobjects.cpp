#include <algorithm>
#include "dstorageobjects.h"
#include "buffer/frombuffer.h"
#include "buffer/tobuffer.h"

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
        buffer = std::vector<uint_fast8_t>();
    }

    Object::~Object() {
        valueMap.clear();
        buffer.clear();
    }

    void Object::setStringValue(const std::string &key, const std::string &value) {
        auto *v = new ValueInternal();
        v->type = STRING;
        new(&v->stringValue) std::string(value);
        valueMap[key] = v;
        didBufferChange = true;
    }

    void Object::setIntValue(const std::string &key, int value) {
        auto *v = new ValueInternal();
        v->type = INT;
        new(&v->intValue) int(value);
        valueMap[key] = v;
        didBufferChange = true;
    }

    void Object::setBoolValue(const std::string &key, bool value) {
        auto *v = new ValueInternal();
        v->type = BOOL;
        new(&v->boolValue) bool(value);
        valueMap[key] = v;
        didBufferChange = true;
    }

    List::List() {
        list = std::vector<ValueInternal>();
    }

    Value *Object::getValue(const std::string &key) {
        auto *value = valueMap[key];
        if (value == nullptr) {
            return nullptr;
        }
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
            case OBJECT:
                v->objectValue = new Object();
                v->objectValue->setFromBuffer(value->objectValue);
                break;
        }
        return v;
    }

    std::vector<uint_fast8_t> List::asBuffer() {
        if (!didBufferChange) {
            return buffer;
        }
        return listToBuffer(this);
    }

    std::vector<uint_fast8_t> Object::asBuffer() {
        if (!didBufferChange) {
            return buffer;
        }
        return objectToBuffer(this);
    }

    void Object::setListValue(const std::string &key, List *value) {
        auto *v = new ValueInternal();
        v->type = LIST;
        new(&v->listValue) std::vector<uint_fast8_t>(value->asBuffer());
        valueMap[key] = v;
        didBufferChange = true;
    }

    void Object::setObjectValue(const std::string &key, Object *value) {
        auto *v = new ValueInternal();
        v->type = OBJECT;
        new(&v->objectValue) std::vector<uint_fast8_t>(value->asBuffer());
        valueMap[key] = v;
        didBufferChange = true;
    }

    void List::addValue(const std::string &value) {
        ValueInternal v{};
        v.type = STRING;
        new(&v.stringValue) std::string(value);
        list.push_back(v);
        didBufferChange = true;
    }

    List::~List() {
        list.clear();
        buffer.clear();
    }

    void Object::setFromBuffer(const std::vector<uint_fast8_t>& vector) {
        this->valueMap = objectFromBuffer(vector)->valueMap;
        didBufferChange = false;
        this->buffer = vector;
    }

    void List::setFromBuffer(const std::vector<uint_fast8_t>& vector) {
        this->list = listFromBuffer(vector)->list;
        didBufferChange = false;
        this->buffer = vector;
    }

    void List::addValue(int value) {
        ValueInternal v{};
        v.type = INT;
        new(&v.intValue) int(value);
        list.push_back(v);
        didBufferChange = true;
    }

    void List::addValue(bool value) {
        ValueInternal v{};
        v.type = BOOL;
        new(&v.boolValue) bool(value);
        list.push_back(v);
        didBufferChange = true;
    }

    void List::addValue(List *value) {
        ValueInternal v{};
        v.type = LIST;
        new(&v.listValue) std::vector<uint_fast8_t>(value->asBuffer());
        list.push_back(v);
        didBufferChange = true;
    }

    void List::addValue(Object *value) {
        ValueInternal v{};
        v.type = OBJECT;
        new(&v.objectValue) std::vector<uint_fast8_t>(value->asBuffer());
        list.push_back(v);
        didBufferChange = true;
    }

    void List::removeValue(int index) {
        list.erase(list.begin() + index);
        didBufferChange = true;
    }

    void Object::removeValue(const std::string &key) {
        valueMap.erase(key);
        didBufferChange = true;
    }

    Value* List::getValue(int index) {
        auto *value = &list[index];
        if (value == nullptr) {
            return nullptr;
        }
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
            case OBJECT:
                v->objectValue = new Object();
                v->objectValue->setFromBuffer(value->objectValue);
                break;
        }
        return v;
    }
}

