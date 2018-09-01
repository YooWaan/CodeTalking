
#include <iostream>
#include <memory>
#include <functional>
#include <condition_variable>
#include <thread>
#include <future>
#include <mutex>
#include <cstdlib>


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

struct Ctx {
    std::mutex mtx_;
    std::condition_variable cond_;
    int thread_max;
    int thread_count = 0;
public:
    Ctx(int m) : thread_max{m} {}
    void notify_done() {
        std::lock_guard<std::mutex> l(mtx_);
        thread_count--;
        cond_.notify_one();
    }
    void wait_thread() {
        std::unique_lock<std::mutex> lk(mtx_);
        //std::cout << "wait ...[" << thread_count << "]" << std::endl;
        cond_.wait(lk, [this] { return thread_count < thread_max; });
        thread_count++;
    }
};

int calc_worker(int size, Ctx *ctx) {
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

    //std::cout << "show::" << size << std::endl;
    //show(lp, size); show(rp, size); 
    //show(ap, size);
    ctx->notify_done();
    return 1;
}

int parallel_matrix(Ctx *ctx, int n, int end) {
    ctx->wait_thread();
    auto ret = std::async(calc_worker, n, ctx);
    if (n < end) {
        return parallel_matrix(ctx, ++n, end) + ret.get();
    }
    return ret.get(); 
}

void run_matrix(int start, int end) {
    //Ctx ctx(std::thread::hardware_concurrency());
    Ctx ctx(8);
    auto result = parallel_matrix(&ctx, start, end);
}

int main(int argc, char* argv[]) {

    if (argc == 3) {
        run_matrix(std::atoi(argv[1]), std::atoi(argv[2]));
    } else {
        std::cout << "Args:" << argc << std::endl;
        std::cout << "cmd start end" << std::endl;
        std::cout << "cmd port" << std::endl;
        std::cout << "cmd num files ...." << std::endl;
    }

    return 0;
}
