#pragma once

#include <iostream>
#include <string>

class DoublyList {
private:
    struct Node {
        std::string data;
        Node* prev;
        Node* next;
        Node(const std::string& value, Node* prevNode, Node* nextNode)
            : data(value), prev(prevNode), next(nextNode) {}
    };

    Node* head_;
    Node* tail_;
    int size_;

public:
    DoublyList();
    ~DoublyList();

    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    DoublyList(DoublyList&& other) noexcept;
    DoublyList& operator=(DoublyList&& other) noexcept;

    void pushFront(const std::string& value);
    void pushBack(const std::string& value);
    void popFront();
    void popBack();
    bool find(const std::string& value) const;
    void remove(const std::string& value);
    void clear();

    int getSize() const;
    bool isEmpty() const;
    void printForward(std::ostream& os = std::cout) const;
    void printBackward(std::ostream& os = std::cout) const;
};
