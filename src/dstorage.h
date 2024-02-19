#ifndef DSTORAGE_DSTORAGE_H
#define DSTORAGE_DSTORAGE_H

#include <map>
#include <vector>
#include <string>
#include <variant>
#include "objects/dstorageobjects.h"

namespace DreamStorage {
    void writeToFile(DreamStorage::Object* value, const char* filename);

    DreamStorage::Object* readFromFile(const char* filename);
}

#endif //DSTORAGE_DSTORAGE_H
