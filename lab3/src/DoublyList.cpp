#include "DoublyList.h"

DoublyList::DoublyList() : head_(nullptr), tail_(nullptr), size_(0) {}

DoublyList::~DoublyList() {
    clear();
}

DoublyList::DoublyList(DoublyList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

DoublyList& DoublyList::operator=(DoublyList&& other) noexcept {
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

void DoublyList::clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    tail_ = nullptr;
    size_ = 0;
}

void DoublyList::pushFront(const std::string& value) {
    Node* node = new Node(value, nullptr, head_);
    if (head_ != nullptr) {
        head_->prev = node;
    } else {
        tail_ = node;
    }
    head_ = node;
    ++size_;
}

void DoublyList::pushBack(const std::string& value) {
    Node* node = new Node(value, tail_, nullptr);
    if (tail_ != nullptr) {
        tail_->next = node;
    } else {
        head_ = node;
    }
    tail_ = node;
    ++size_;
}

void DoublyList::popFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* tmp = head_;
    head_ = head_->next;
    if (head_ != nullptr) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    delete tmp;
    --size_;
}

void DoublyList::popBack() {
    if (tail_ == nullptr) {
        return;
    }
    Node* tmp = tail_;
    tail_ = tail_->prev;
    if (tail_ != nullptr) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }
    delete tmp;
    --size_;
}

bool DoublyList::find(const std::string& value) const {
    const Node* cur = head_;
    while (cur != nullptr) {
        if (cur->data == value) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void DoublyList::remove(const std::string& value) {
    Node* cur = head_;
    while (cur != nullptr) {
        if (cur->data == value) {
            if (cur->prev != nullptr) {
                cur->prev->next = cur->next;
            } else {
                head_ = cur->next;
            }
            if (cur->next != nullptr) {
                cur->next->prev = cur->prev;
            } else {
                tail_ = cur->prev;
            }
            delete cur;
            --size_;
            return;
        }
        cur = cur->next;
    }
}

int DoublyList::getSize() const {
    return size_;
}

bool DoublyList::isEmpty() const {
    return size_ == 0;
}

void DoublyList::printForward(std::ostream& os) const {
    const Node* cur = head_;
    while (cur != nullptr) {
        os << cur->data << " ";
        cur = cur->next;
    }
    os << "\n";
}

void DoublyList::printBackward(std::ostream& os) const {
    const Node* cur = tail_;
    while (cur != nullptr) {
        os << cur->data << " ";
        cur = cur->prev;
    }
    os << "\n";
}
