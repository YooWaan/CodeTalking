
#include <iostream>
#include <memory>
#include <functional>


// g++ -std=c++11 matrix.cpp -o matrix

template<typename Functor>
void matrix(int** value, int size, Functor func) {
  for (int i = 0; i < size ;i++) {
    for (int n = 0; n < size;n++) {
      value[i][n] = func(i, n);
    }
  }    
}

void show(int ** value, int size) {
    for (int i = 0; i < size ;i++) {
        std::cout << '[';
        for (int n = 0; n < size ;n++) {
            std::cout << value[i][n];
        }
        std::cout << ']' << std::endl;
    }
}

void mem(int*** value, int size) {
    int*** adr = value;
    *value = new int*[size];
    for (int i = 0; i < size ;i++) {
        (*value)[i] = new int[size];
        for (int n = 0; n < size ; n++) {
            (*value)[i][n] = 0;
        }
    }
}

void calc(int size) {
  /*
  auto cl = [](int** v) {
    delete[] v;
  };

  auto rcl = [](unique_ptr<int> v) {
    v.reset();
  };
new int*[size], cl
  , std::function<void(int**)>
      */

  std::unique_ptr<std::unique_ptr<int[]>[]> lm(new std::unique_ptr<int[]>[size]);
  std::unique_ptr<std::unique_ptr<int[]>[]> rm(new std::unique_ptr<int[]>[size]);
  for (int i = 0; i < size ;i++) {
    std::unique_ptr<int> lr(new int[size]);
    std::unique_ptr<int> rr(new int[size]);
    for (int n = 0; n < size ; n++) {
      lr[n] = i+1;
      rr[n] = n+1;
    }
    lm[i] = std::move(lr);
    rm[i] = std::move(rr);
  }

  show(lm.get(), size);
  show(rm.get(), size);

}


int main(int argc, char* argv[]) {

    int size = 3;

    calc(size);

    /*
    int** value; int** rg;
    mem(&value, size);
    mem(&rg, size);

    auto ln = [] (int r, int c) { return r+1; };
    auto rn = [] (int r, int c) { return c+1; };
    matrix(value, size, ln);
    matrix(rg, size, rn);
    show(value, size);
    show(rg, size);
    */
    return 0;
}
