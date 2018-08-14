
#include <iostream>


void left(int** value, int size) {
    for (int i = 0; i < size ;i++) {
        for (int n = 0; n < size;n++) {
            value[i][n] = i+1;
        }
    }    
}

void right(int** value, int size) {
    for (int i = 0; i < size ;i++) {
        for (int n = 0; n < size;n++) {
            value[i][n] = n+1;
        }
    }    
}

/*
void calc(int size) {

    int **left = alloc();

}
*/

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
    std::cout << *value << std::endl;
    *value = new int*[size];
    for (int i = 0; i < size ;i++) {
        (*value)[i] = new int[size];
        for (int n = 0; n < size ; n++) {
            (*value)[i][n] = 0;
        }
    }
}


int main(int argc, char* argv[]) {

    int size = 3;
    int** value; int** rg;

    
    mem(&value, size);
    mem(&rg, size);

    left(value, size);
    right(rg, size);

    show(value, size);
    show(rg, size);

    return 0;
}