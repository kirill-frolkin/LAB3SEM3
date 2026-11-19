#include "Serializer.h"
#include <cstdint>
#include <fstream>
#include <iostream>

bool Serializer::saveBinary(const DynamicArray& arr, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    auto count = static_cast<std::int32_t>(arr.getSize());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (int i = 0; i < arr.getSize(); ++i) {
        std::string val = arr.get(i);
        auto len = static_cast<std::int32_t>(val.size());
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) {
            out.write(val.data(), len);
        }
    }

    return static_cast<bool>(out);
}

DynamicArray Serializer::loadBinary(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Не удалось открыть файл для чтения: " << filename << "\n";
        return DynamicArray();
    }

    std::int32_t count = 0;
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)) || count < 0) {
        return DynamicArray();
    }

    DynamicArray arr(count > 0 ? count : 1);
    for (std::int32_t i = 0; i < count; ++i) {
        std::int32_t len = 0;
        if (!in.read(reinterpret_cast<char*>(&len), sizeof(len)) || len < 0) {
            return DynamicArray();
        }
        std::string val(static_cast<std::size_t>(len), '\0');
        if (len > 0 && !in.read(&val[0], len)) {
            return DynamicArray();
        }
        arr.pushBack(val);
    }

    return arr;
}
