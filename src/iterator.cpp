#include <iostream>
#include <vector>

struct Node {
  Node(int val) : next_(nullptr), prev_(nullptr), value_(val) {}
  Node *next_;
  Node *prev_;
  int value_;
};

class DLLIter {
public:
  DLLIter(Node *head) : curr_(head) {}

  DLLIter operator++() {
    curr_ = curr_->next_;
    return *this;
  }
  DLLIter operator++(int) {
    DLLIter tmp = *this;
    ++(*this);
    return tmp;
  }
  bool operator==(const DLLIter &other) { return this->curr_ == other.curr_; }
  bool operator!=(const DLLIter &other) { return this->curr_ != other.curr_; }
  int operator*() { return curr_->value_; }

private:
  Node *curr_;
};

class DLL {
public:
  // DLL class constructor.
  DLL() : head_(nullptr), size_(0) {}

  // Destructor should delete all the nodes by iterating through them.
  ~DLL() {
    Node *current = head_;
    while (current != nullptr) {
      Node *next = current->next_;
      delete current;
      current = next;
    }
    head_ = nullptr;
  }
  // Function for inserting val at the head of the DLL.
  void InsertAtHead(int val) {
    Node *new_node = new Node(val);
    new_node->next_ = head_;

    if (head_ != nullptr) {
      head_->prev_ = new_node;
    }

    head_ = new_node;
    size_ += 1;
  }

  DLLIter begin() { return DLLIter(head_); }
  DLLIter end() { return DLLIter(nullptr); }

private:
  Node *head_{nullptr};
  size_t size_;
};

int main() {
  // Creating a DLL and inserting elements into it.
  DLL dll;
  auto nums = std::vector<int>{6, 5, 4, 3, 2, 1};
  for (const auto &num : nums) {
    dll.InsertAtHead(num);
  }

  std::cout
      << "Printing elements of the DLL dll via prefix increment operator\n";
  for (DLLIter iter = dll.begin(); iter != dll.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  std::cout
      << "Printing elements of the DLL dll via postfix increment operator\n";
  for (DLLIter iter = dll.begin(); iter != dll.end(); iter++) {
    std::cout << *iter << " ";
  }

  std::cout << std::endl;
  return 0;
}
