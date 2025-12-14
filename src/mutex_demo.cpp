/**
 * @file mutex.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ STL mutex.
 */

// This program shows a small example of the usage of std::mutex. The
// std::mutex class provides the mutex synchronization primitive.

// Includes std::cout (printing) for demo purposes.
#include <functional>
#include <iostream>
// Includes the mutex library header.
#include <mutex>
// Includes the thread library header.
#include <ostream>
#include <thread>

// Defining a global count variable and a mutex to be used by both threads.
struct safe_cnt {
  std::mutex m; // not needed construct
  int count_;
  safe_cnt() : count_(0) {};
  safe_cnt(int n) : count_(n) {};
  void add(int);
};

std::ostream &operator<<(std::ostream &os, safe_cnt &cnt) {
  os << cnt.count_;
  return os;
}

void safe_cnt::add(int accr) {
  m.lock();
  count_ += accr;
  m.unlock();
  return;
}

void safe_add(safe_cnt &cnt, int accr) {
  std::cout << "start exec cnt is " << cnt << "\n";
  cnt.add(accr);
}

int main() {
  safe_cnt cnt;
  int n = 100;
  std::vector<std::thread> threads;
  threads.reserve(n);
  for (int i = 0; i < n; i++) {
    threads.emplace_back(safe_add, std::ref(cnt), 10);
  }
  for (auto &t : threads) {
    t.join();
  }
  std::cout << "Printing count: " << cnt << std::endl;
  return 0;
}
