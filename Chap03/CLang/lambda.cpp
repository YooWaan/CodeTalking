#include <iostream>

std::function<int()> GetClosure(int *cnt) {
  auto c = [&, cnt]() {
    *cnt = *cnt + 1;
    return *cnt;
  };
  return c;
}


int main(void) {

  auto n = [](int a, int b){ return a + b;}(1,2);
  auto f = [](int a, int b){ return a + b;};

  std::cout << "calc -> " << n << std::endl;
  std::cout << "func -> " << f(1,2) << std::endl;

  int count = 0;
  auto c = GetClosure(&count);
  std::cout << "cnt 1 -> " << c() << std::endl;
  std::cout << "cnt 2 -> " << c() << std::endl;
  std::cout << "cnt 3 -> " << c() << std::endl;
  std::cout << "cnt 4 -> " << c() << std::endl;

  std::cout << "local cnt-> " << count << std::endl;

  return 0;
}


