#include "Queue.h"

Queue::Queue() : head_(nullptr), tail_(nullptr), count_(0) {}

Queue::~Queue() {
    clear();
}

Queue::Queue(Queue&& other) noexcept
    : head_(other.head_), tail_(other.tail_), count_(other.count_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.count_ = 0;
}

Queue& Queue::operator=(Queue&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        count_ = other.count_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.count_ = 0;
    }
    return *this;
}

void Queue::clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    tail_ = nullptr;
    count_ = 0;
}

void Queue::push(const std::string& value) {
    Node* node = new Node(value, nullptr);
    if (tail_ == nullptr) {
        head_ = node;
        tail_ = node;
    } else {
        tail_->next = node;
        tail_ = node;
    }
    ++count_;
}

void Queue::pop() {
    if (head_ == nullptr) {
        return;
    }
    Node* tmp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr;
    }
    delete tmp;
    --count_;
}

std::string Queue::front() const {
    if (head_ == nullptr) {
        return "";
    }
    return head_->data;
}

int Queue::size() const {
    return count_;
}

bool Queue::isEmpty() const {
    return head_ == nullptr;
}
