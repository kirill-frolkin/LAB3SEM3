#pragma once

#include <iostream>
#include <string>

class DynamicArray {
private:
    std::string* data_;
    int size_;
    int capacity_;

    void ensureCapacity(int needed);

public:
    explicit DynamicArray(int initialCapacity = 8);
    ~DynamicArray();

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    void pushBack(const std::string& value);
    void popBack();
    std::string get(int index) const;
    void set(int index, const std::string& value);
    void removeAt(int index);
    void clear();

    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
    void print(std::ostream& os = std::cout) const;
};
