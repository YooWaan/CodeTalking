
#include <fstream>
#include <iostream>
#include <future>
#include <thread>
#include <vector>

#define OK 0
#define ERR 1

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


int count(char* filename) {

    std::ifstream fin(filename,  std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "cant open file " << filename << std::endl;
        return ERR;
    }

    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.seekg(0, fin.beg);

    char* buffer = new char [length];
    fin.read(buffer, length);
    if (!fin) {
        std::cerr << "cant read file " << filename << std::endl;
        return ERR;
    }

    fin.close();

    std::cout << buffer << std::endl;

    delete [] buffer;
    return OK;    
}





int main(int argc, char* argv[]) {

/*
    for (int i = 1; i < argc ; i++) {
        printf("file=%s\n", argv[i]);
        count(argv[i]);
        //
    }
*/
    async();
    return 0;
}




