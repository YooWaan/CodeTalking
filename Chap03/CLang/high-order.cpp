#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

auto filter = [](int x) {return x % 2 == 0;};
auto map    = [](int x) {return 2 * x;};
auto sum    = [](int a, int b) {return a + b;};

std::function<int(std::vector<int>)> Currying() {
  auto fn = [](std::vector<int> src) {
    std::vector<int> data;
    copy_if(src.begin(), src.end(), back_inserter(data), filter);
    transform(data.begin(), data.end(), data.begin(), map);
    return accumulate(data.begin(), data.end(), 0, sum);
  };
  return fn;
}

int main(void) {
  std::vector<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> data;

  auto pln =[](std::string msg, std::vector<int> dat) {
    std::cout << msg << '[' ;
    for (auto&& e : dat) {
      std::cout << ' ' << e ;
    }
    std::cout << " ]" << std::endl;
  };

  // arguments
  copy_if(src.begin(), src.end(), back_inserter(data), filter);
  pln("filter-> ", data);

  data.clear();
  copy_if(src.begin(), src.end(), back_inserter(data), filter);
  transform(data.begin(), data.end(), data.begin(), map);
  pln("filter-> map-> ", data);

  data.clear();
  copy_if(src.begin(), src.end(), back_inserter(data), filter);
  transform(data.begin(), data.end(), data.begin(), map);
  auto result = accumulate(data.begin(), data.end(), 0, sum);
  std::cout << "filter-> map-> reduce-> " << result << std::endl;

  // currying
  auto sumFn = Currying();
  std::cout << "currying-> " << sumFn(src) << std::endl;
}
