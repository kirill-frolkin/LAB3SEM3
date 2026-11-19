#pragma once

#include <iostream>
#include <string>

class SinglyList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value, Node* nextNode) : data(value), next(nextNode) {}
    };

    Node* head_;
    Node* tail_;
    int size_;

public:
    SinglyList();
    ~SinglyList();

    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;

    SinglyList(SinglyList&& other) noexcept;
    SinglyList& operator=(SinglyList&& other) noexcept;

    void pushFront(const std::string& value);
    void pushBack(const std::string& value);
    void popFront();
    void popBack();
    bool find(const std::string& value) const;
    void remove(const std::string& value);
    void clear();

    int getSize() const;
    bool isEmpty() const;
    std::string get(int index) const;
    void print(std::ostream& os = std::cout) const;
};
