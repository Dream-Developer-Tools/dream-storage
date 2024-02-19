#ifndef DSTORAGE_DSTORAGEOBJECTS_H
#define DSTORAGE_DSTORAGEOBJECTS_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "../tokens.h"

namespace DreamStorage {

    class Object;
    class List;

    enum ValueType {
        INT,
        STRING,
        BOOL,
        LIST,
        OBJECT
    };

    struct ValueInternal {
        ValueType type;
        union {
            int intValue;
            bool boolValue;
            std::string stringValue;
            std::vector<uint_fast8_t> listValue;
            std::vector<uint_fast8_t> objectValue;
        };

        ValueInternal() : type(INT), intValue(0) {}

        ValueInternal(const ValueInternal& other) : type(other.type) {
            switch (type) {
                case INT:
                    new (&intValue) int(other.intValue);
                    break;
                case BOOL:
                    new (&boolValue) bool(other.boolValue);
                    break;
                case STRING:
                    new (&stringValue) std::string(other.stringValue);
                    break;
                case LIST:
                    listValue = other.listValue;
                    break;
                case OBJECT:
                    objectValue = other.objectValue;
                    break;
            }
        }

        ValueInternal& operator=(const ValueInternal& other) {
            if (this != &other) {
                // Cleanup current resources if needed
                if (type == STRING) {
                    stringValue.~basic_string();
                }

                type = other.type;

                switch (type) {
                    case INT:
                        intValue = other.intValue;
                        break;
                    case BOOL:
                        boolValue = other.boolValue;
                        break;
                    case STRING:
                        new (&stringValue) std::string(other.stringValue);
                        break;
                }
            }
            return *this;
        }

        ~ValueInternal() {
            if (type == STRING) {
                stringValue.~basic_string();
            } else if (type == LIST) {
                listValue.~vector();
            } else if (type == OBJECT) {
                objectValue.~vector();
            }
        }
    };

    struct Value {
        ValueType type;
        union {
            int intValue;
            bool boolValue;
            std::string stringValue;
            List* listValue;
            Object* objectValue;
        };

        Value() : type(INT), intValue(0) {};

        Value(const ValueInternal& other);

        ~Value() {
            if (type == STRING) {
                stringValue.~basic_string();
            }
        }
    };


    class Object {
    public:
        std::unordered_map<std::string, ValueInternal*> valueMap;

        Object();
        ~Object();

        void setFromBuffer(std::vector<uint_fast8_t> buffer);

        void setIntValue(const std::string& key, int value);
        void setStringValue(const std::string& key, const std::string& value);
        void setBoolValue(const std::string& key, bool value);
        void setListValue(const std::string& key, List* value);
        void setObjectValue(const std::string& key, Object* value);

        Value* getValue(const std::string& key);

        void removeValue(const std::string& key);

        std::vector<uint_fast8_t> asBuffer();
    };

    class List {
    public:
        std::vector<ValueInternal> list;

        List();
        List(List* other) : list(other->list) {}
        ~List();

        void setFromBuffer(std::vector<uint_fast8_t> buffer);

        void addValue(int value);
        void addValue(const std::string& value);
        void addValue(bool value);
        void addValue(List* value);
        void addValue(Object* value);

        ValueInternal getValue(int index);

        void removeValue(int index);

        std::vector<uint_fast8_t> asBuffer();
    };
}

#endif
