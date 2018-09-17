
#include <fstream>
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <memory>
#include <cstring>
 


#define OK 0
#define ERR 1

/*
int foo() { std::cout << "foo>" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(1000)); return 10; }

void async() {
    using namespace std;
    vector<future<int>> fs;
    fs.push_back(async(launch::async, foo));
    fs.push_back(async(launch::async, foo));
    fs.push_back(async(launch::async, foo));


    //auto result = when_any(fs.begin(), fs.end());

    int sum = 0;
    for (auto &f : fs) {
        int value = f.get();
        cout << "v:" << value << endl; 
        sum += value;
    }
    cout << "sum:" << sum << endl;
}
*/

typedef struct {
    int bytes;
    int words;
    int lines;
} Count;


Count char_count(char* buffer) {
    Count c = {0, 0, 0};
    std::unique_ptr<char[]> ss(buffer);
    bool inword = false;
    for (int i =0, len = std::strlen(buffer); i < len ;i++) {
        c.bytes++;
        if (buffer[i] == ' ') {
            if (inword) {
                inword = false;
                c.words++;
            }
        } else if (buffer[i] == '\n') {
            c.lines++;
        } else {
            inword = true;
        }
    }
    return c;
}


int count(char* filename) {

    std::ifstream fin(filename,  std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "cant open file " << filename << std::endl;
        return ERR;
    }

    int bufsize = 10;    

    std::vector<std::future<Count>> futures;
    std::unique_ptr<char[]> buffer(new char [bufsize]);

    do {
        auto ptr = buffer.get();
        fin.read(ptr, bufsize);
        if (fin.bad()) {
            std::cerr << "cant read file " << filename << std::endl;
            return ERR;
        }

        // copy
        auto rsz = fin.gcount();
        auto buf = new char[rsz+1];
        std::memcpy(buf, ptr, rsz);
        buf[rsz] = '\0';

        // count
        //std::cout << "buf:" << buf << ", " << ptr << std::endl;
        auto ft = std::async(std::launch::async, char_count, buf);
        futures.push_back(std::move(ft));

    } while(!fin.eof());

    fin.close();

    Count cnt = {0, 0, 0};
    for (auto& ft : futures) {
        try {
            Count c = ft.get();
            cnt.bytes += c.bytes;
            cnt.words += c.words;
            cnt.lines += c.lines;
        } catch (std::future_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "B;" << cnt.bytes << ",W:" << cnt.words << ",L:" << cnt.lines << std::endl;

    return OK;    
}





int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cout << "cmd times files...." << std::endl;
        return 1;
    }
    for (int i = 2; i < argc ; i++) {
        printf("file=%s\n", argv[i]);
        count(argv[i]);
    }

    return 0;
}




