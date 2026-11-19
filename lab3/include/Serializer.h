#pragma once

#include <string>
#include "DynamicArray.h"

class Serializer {
public:
    static bool saveBinary(const DynamicArray& arr, const std::string& filename);
    static DynamicArray loadBinary(const std::string& filename);
};
