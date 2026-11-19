#pragma once

#include <iostream>
#include <string>

class Stack {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value, Node* nextNode) : data(value), next(nextNode) {}
    };

    Node* head_;
    int count_;

public:
    Stack();
    ~Stack();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;

    void push(const std::string& value);
    void pop();
    void clear();

    std::string peek() const;
    int size() const;
    bool isEmpty() const;
};
