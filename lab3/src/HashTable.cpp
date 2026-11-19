#include "HashTable.h"
#include <numeric>

HashTable::HashTable() : buckets_{}, count_(0) {}

HashTable::~HashTable() {
    clear();
}

void HashTable::clear() {
    for (auto& bucket : buckets_) {
        Node* cur = bucket;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        bucket = nullptr;
    }
    count_ = 0;
}

int HashTable::hashString(const std::string& s) const {
    return std::accumulate(s.begin(), s.end(), 0, [](int acc, char c) {
        return (acc * HASH_BASE + static_cast<unsigned char>(c)) % TABLE_SIZE;
    });
}

void HashTable::add(const std::string& key) {
    int idx = hashString(key);
    Node* cur = buckets_[idx];
    while (cur != nullptr) {
        if (cur->key == key) {
            return;
        }
        cur = cur->next;
    }
    buckets_[idx] = new Node(key, buckets_[idx]);
    ++count_;
}

void HashTable::remove(const std::string& key) {
    int idx = hashString(key);
    Node* cur = buckets_[idx];
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->key == key) {
            if (prev != nullptr) {
                prev->next = cur->next;
            } else {
                buckets_[idx] = cur->next;
            }
            delete cur;
            --count_;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

bool HashTable::contains(const std::string& key) const {
    int idx = hashString(key);
    const Node* cur = buckets_[idx];
    while (cur != nullptr) {
        if (cur->key == key) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

int HashTable::size() const {
    return count_;
}

bool HashTable::isEmpty() const {
    return count_ == 0;
}
