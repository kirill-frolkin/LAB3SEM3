#pragma once

#include <iostream>
#include <string>

class Queue {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value, Node* nextNode) : data(value), next(nextNode) {}
    };

    Node* head_;
    Node* tail_;
    int count_;

public:
    Queue();
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;

    void push(const std::string& value);
    void pop();
    void clear();

    std::string front() const;
    int size() const;
    bool isEmpty() const;
};
