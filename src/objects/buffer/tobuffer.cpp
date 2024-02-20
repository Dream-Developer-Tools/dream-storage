#include "tobuffer.h"

namespace DreamStorage {

    std::vector<uint_fast8_t> objectToBuffer(Object *value) {
        // declare a buffer to store the bytes
        std::vector<uint_fast8_t> buffer;
        // loop through valueMap
        for (auto [key, val]: value->valueMap) {
            // check if the value is a string
            switch (val->type) {
                case STRING:
                    // add the key to the buffer
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: key) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::IS));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: val->stringValue) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case INT:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: key) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::IS));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::NUMBER_BEGIN));
                    for (char c: std::to_string(val->intValue)) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::NUMBER_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case BOOL:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: key) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::IS));
                    if (val->boolValue) {
                        buffer.push_back(static_cast<uint_fast8_t>(Token::TRUE));
                    } else {
                        buffer.push_back(static_cast<uint_fast8_t>(Token::FALSE));
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case LIST:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: key) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::IS));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::LIST_BEGIN));
                    for (uint_fast8_t byte: val->listValue) {
                        buffer.push_back(byte);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::LIST_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
                case OBJECT:
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_BEGIN));
                    for (char c: key) {
                        buffer.push_back(c);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::STRING_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::IS));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::OBJECT_BEGIN));
                    for (uint_fast8_t byte: val->objectValue) {
                        buffer.push_back(byte);
                    }
                    buffer.push_back(static_cast<uint_fast8_t>(Token::OBJECT_END));
                    buffer.push_back(static_cast<uint_fast8_t>(Token::END_OF_LINE));
                    break;
            }
        }
        return buffer;
    }

    std::vector<uint_fast8_t> listToBuffer(List *value) {
        std::vector<uint_fast8_t> buffer = std::vector<uint_fast8_t>();
        for (const ValueInternal &val: value->list) {
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

}