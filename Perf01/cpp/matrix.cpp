
#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>


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
            std::cout << value[i][n] << ' ';
        }
        std::cout << ']' << std::endl;
    }
}

template<typename Functor>
void mem(int*** value, int size, Functor func) {
    int*** adr = value;
    *value = new int*[size];
    for (int i = 0; i < size ;i++) {
        (*value)[i] = new int[size];
        for (int n = 0; n < size ; n++) {
            (*value)[i][n] = 0;
        }
    }
    matrix(*value, size, func);
}

void mul(int** left, int** right, int** ans, int size) {
    for (int i = 0; i < size ;i++) {
        for (int n = 0; n < size ; n++) {
            for (int m = 0; m < size ; m++) {
                ans[i][n] += left[i][m] * right[m][n];
            }
        }
    }
}

void calc_worker(int size, std::mutex& mtx, int& counter) {
    auto ln = [] (int r, int c) { return r+1; };
    auto rn = [] (int r, int c) { return c+1; };
    auto zero = [] (int r, int c) { return 0; };

    std::unique_ptr<int*[]> lmx(new int*[size]);
    std::unique_ptr<int*[]> rmx(new int*[size]);
    std::unique_ptr<int*[]> ans(new int*[size]);

    auto lp = lmx.get();
    auto rp = rmx.get();
    auto ap = ans.get();

    mem(&lp, size, ln);
    mem(&rp, size, rn);
    mem(&ap, size, zero);

    mul(lp, rp, ap, size);

    //std::cout << "show" << std::endl;
    //show(lp, size); show(rp, size); 
    show(ap, size);
    mtx.lock();
    counter ++;
    mtx.unlock();
}


int main(int argc, char* argv[]) {

    int size = 3;
    std::mutex mtx;
    int counter = 0;
    std::vector<std::thread> threads(size);

    int i = 1;
    for (auto& th : threads) {
        th = std::thread(calc_worker, i++, std::ref(mtx), std::ref(counter));
    }

    for (std::thread& th : threads) {
        th.join();
    }
    //std::for_each(threads.begin(), threads.end(), [](std::thread& x) {x.join();});

    mtx.lock();
    std::cout << "count;" << counter << std::endl;
    mtx.unlock();

    return 0;
}
