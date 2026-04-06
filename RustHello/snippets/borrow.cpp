#include <stdio.h>

void fnline(const char* title) {
    printf("--- %s:: --------------------------------------------------\n", title);
}

void print_string(const char* ss) {
    fnline("print_string");
    const char* tmp = ss;
    printf("hi, ss: %s\nhi, tmp: %s\n borrowed value is no there\n", ss, tmp);
    printf(" ss => Stack addr: %p, Heap addr: %p,value: %s\n", &ss, ss, ss);
    printf("tmp => Stack addr: %p, Heap addr: %p,value: %s\n", &tmp, tmp, tmp);
}

int main() {

    const char* ss = "hello world";
    print_string(ss);


    return 0;
}