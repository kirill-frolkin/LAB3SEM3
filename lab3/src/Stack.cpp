#include "Stack.h"

Stack::Stack() : head_(nullptr), count_(0) {}

Stack::~Stack() {
    clear();
}

Stack::Stack(Stack&& other) noexcept : head_(other.head_), count_(other.count_) {
    other.head_ = nullptr;
    other.count_ = 0;
}

Stack& Stack::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        count_ = other.count_;
        other.head_ = nullptr;
        other.count_ = 0;
    }
    return *this;
}

void Stack::clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    count_ = 0;
}

void Stack::push(const std::string& value) {
    head_ = new Node(value, head_);
    ++count_;
}

void Stack::pop() {
    if (head_ == nullptr) {
        return;
    }
    Node* tmp = head_;
    head_ = head_->next;
    delete tmp;
    --count_;
}

std::string Stack::peek() const {
    if (head_ == nullptr) {
        return "";
    }
    return head_->data;
}

int Stack::size() const {
    return count_;
}

bool Stack::isEmpty() const {
    return head_ == nullptr;
}
