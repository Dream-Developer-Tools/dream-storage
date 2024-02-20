#ifndef DSTORAGE_TOBUFFER_H
#define DSTORAGE_TOBUFFER_H

#include "../dstorageobjects.h"

namespace DreamStorage {
    std::vector<uint_fast8_t> objectToBuffer(Object *value);
    std::vector<uint_fast8_t> listToBuffer(List *value);
}

#endif
