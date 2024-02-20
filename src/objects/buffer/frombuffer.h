#ifndef DSTORAGE_FROMBUFFER_H
#define DSTORAGE_FROMBUFFER_H

#include <cstdint>
#include <vector>
#include "../dstorageobjects.h"

namespace DreamStorage {
    DreamStorage::Object *objectFromBuffer(const std::vector<uint_fast8_t>& buffer);

    DreamStorage::List *listFromBuffer(const std::vector<uint_fast8_t>& buffer);
}

#endif
