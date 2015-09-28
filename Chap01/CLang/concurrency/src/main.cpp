#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

#define NOW chrono::high_resolution_clock::now()
#define MILLI chrono::milliseconds

int fib(int n) {
  if (n <= 1) { return n; }
  return fib(n-1) + fib(n-2);
}

void worker(int v, mutex& mtx, int& counter ) {
  int n =fib(v);
  mtx.lock();
  counter = counter + 1;
  mtx.unlock();
  cout << "fib(" << v << ") => " << n << ", counter=>" << counter << endl;
}


int main(void) {
  vector<std::thread> threads;
  mutex mtx;
  int counter = 0;
  int nums[] = { 42, 30, 40, 45, 40 };

  auto start = NOW;
  // sequencial exec
  for (int i = 0; i < 5 ;i++) {
    worker(nums[i], std::ref(mtx), std::ref(counter));
  }
  auto end = NOW;
  MILLI milli = chrono::duration_cast<MILLI>(end - start);
  cout << "---- sequencial done. [" << milli.count() << "] ------" << endl;

  // multi thread
  start = NOW;
  for (int i = 0; i < 5 ;i++) {
    threads.push_back(thread(worker, nums[i], std::ref(mtx), std::ref(counter)));
  }
  for (auto& th : threads) {
    th.join();
  }
  end = NOW;
  milli = chrono::duration_cast<MILLI>(end - start);
  cout << "---- multithread done. [" << milli.count() << "] ------" << endl;

  mtx.lock();
  cout << "counter->" << counter << endl;
  mtx.unlock();
  return 0;
}
