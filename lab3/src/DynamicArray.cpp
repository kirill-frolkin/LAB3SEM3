#include "DynamicArray.h"
#include <utility>

DynamicArray::DynamicArray(int initialCapacity) {
    int cap = (initialCapacity < 1) ? 1 : initialCapacity;
    data_ = new std::string[cap];
    size_ = 0;
    capacity_ = cap;
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

void DynamicArray::ensureCapacity(int needed) {
    if (needed <= capacity_) {
        return;
    }
    int newCap = (capacity_ > 0) ? capacity_ : 1;
    while (newCap < needed) {
        newCap *= 2;
    }
    auto* newData = new std::string[newCap];
    for (int i = 0; i < size_; ++i) {
        newData[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
}

void DynamicArray::pushBack(const std::string& value) {
    ensureCapacity(size_ + 1);
    data_[size_++] = value;
}

void DynamicArray::popBack() {
    if (size_ > 0) {
        --size_;
        data_[size_].clear();
    }
}

std::string DynamicArray::get(int index) const {
    if (index < 0 || index >= size_) {
        return "";
    }
    return data_[index];
}

void DynamicArray::set(int index, const std::string& value) {
    if (index < 0 || index >= size_) {
        return;
    }
    data_[index] = value;
}

void DynamicArray::removeAt(int index) {
    if (index < 0 || index >= size_) {
        return;
    }
    for (int i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
    data_[size_].clear();
}

void DynamicArray::clear() {
    for (int i = 0; i < size_; ++i) {
        data_[i].clear();
    }
    size_ = 0;
}

int DynamicArray::getSize() const {
    return size_;
}

int DynamicArray::getCapacity() const {
    return capacity_;
}

bool DynamicArray::isEmpty() const {
    return size_ == 0;
}

void DynamicArray::print(std::ostream& os) const {
    os << "[";
    for (int i = 0; i < size_; ++i) {
        os << data_[i];
        if (i < size_ - 1) {
            os << ", ";
        }
    }
    os << "]\n";
}
