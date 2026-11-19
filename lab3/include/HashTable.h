#pragma once

#include <array>
#include <string>

class HashTable {
private:
    struct Node {
        std::string key;
        Node* next;
        Node(const std::string& k, Node* nextNode) : key(k), next(nextNode) {}
    };

    static constexpr int TABLE_SIZE = 1021;
    static constexpr int HASH_BASE = 131;

    std::array<Node*, TABLE_SIZE> buckets_;
    int count_;

    int hashString(const std::string& s) const;

public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void add(const std::string& key);
    void remove(const std::string& key);
    bool contains(const std::string& key) const;
    void clear();

    int size() const;
    bool isEmpty() const;
};
