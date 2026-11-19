#include "SinglyList.h"

SinglyList::SinglyList() : head_(nullptr), tail_(nullptr), size_(0) {}

SinglyList::~SinglyList() {
    clear();
}

SinglyList::SinglyList(SinglyList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

SinglyList& SinglyList::operator=(SinglyList&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

void SinglyList::clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    tail_ = nullptr;
    size_ = 0;
}

void SinglyList::pushFront(const std::string& value) {
    Node* node = new Node(value, head_);
    head_ = node;
    if (tail_ == nullptr) {
        tail_ = node;
    }
    ++size_;
}

void SinglyList::pushBack(const std::string& value) {
    Node* node = new Node(value, nullptr);
    if (tail_ == nullptr) {
        head_ = node;
        tail_ = node;
    } else {
        tail_->next = node;
        tail_ = node;
    }
    ++size_;
}

void SinglyList::popFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* tmp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr;
    }
    delete tmp;
    --size_;
}

void SinglyList::popBack() {
    if (head_ == nullptr) {
        return;
    }
    if (head_ == tail_) {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return;
    }
    Node* cur = head_;
    while (cur->next != tail_) {
        cur = cur->next;
    }
    delete tail_;
    cur->next = nullptr;
    tail_ = cur;
    --size_;
}

bool SinglyList::find(const std::string& value) const {
    const Node* cur = head_;
    while (cur != nullptr) {
        if (cur->data == value) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void SinglyList::remove(const std::string& value) {
    if (head_ == nullptr) {
        return;
    }
    if (head_->data == value) {
        popFront();
        return;
    }
    Node* prev = head_;
    Node* cur = head_->next;
    while (cur != nullptr) {
        if (cur->data == value) {
            prev->next = cur->next;
            if (cur == tail_) {
                tail_ = prev;
            }
            delete cur;
            --size_;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int SinglyList::getSize() const {
    return size_;
}

bool SinglyList::isEmpty() const {
    return size_ == 0;
}

std::string SinglyList::get(int index) const {
    if (index < 0 || index >= size_) {
        return "";
    }
    const Node* cur = head_;
    for (int i = 0; i < index && cur != nullptr; ++i) {
        cur = cur->next;
    }
    return cur != nullptr ? cur->data : "";
}

void SinglyList::print(std::ostream& os) const {
    if (head_ == nullptr) {
        os << "список пуст\n";
        return;
    }
    const Node* cur = head_;
    while (cur != nullptr) {
        os << cur->data;
        if (cur->next != nullptr) {
            os << " -> ";
        }
        cur = cur->next;
    }
    os << " -> NULL\n";
}
