#include <iostream>

void line(const char* title) {
    std::cout << "--- " << title << ":: --------------------------------------------------" << std::endl;
}

struct Number {
    int value;

    ~Number() {
        std::cout << "Destruct:[" << (void*)this << "] [value: " << &value << "] " << value << std::endl;
    }
};

int main() {

    {
        const Number n = { 10 };
        line("const Number");
        std::cout << "Number:  [" << &n << "] [value: " << &n.value << "] " << n.value << std::endl;

        //const Number* p = &n;
        //p->value = 100; // Error: assignment of read-only member 'Number::value'
    }

    {
        line("Number Variable");
        Number num = { 20 };
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
        num.value += 5;
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
        num.value += 10;
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
    }

    {
        line("unique ptr Number*");
        std::unique_ptr<Number> p = std::make_unique<Number>();
        p->value = 30;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
        p->value += 5;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
        p->value += 10;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
    }

    {
        line("shared ptr Number*");
        std::shared_ptr<Number> p = std::make_shared<Number>();
        p->value = 40;
        std::cout << "Shared_ptr<Number>: [" << p << "] [value: " << &p->value << "] " << p->value << ", Use Count: " << p.use_count() << std::endl;

        {
            std::shared_ptr<Number> s_p = p;
            std::cout << "Shared_ptr<Number> Clone: [" << s_p << "] [value: " << &s_p->value << "] " << s_p->value << ", Use Count: " << s_p.use_count() << std::endl;
        }

        {
            std::shared_ptr<Number> s_p = p;
            std::cout << "Shared_ptr<Number> Clone: [" << s_p << "] [value: " << &s_p->value << "] " << s_p->value << ", Use Count: " << s_p.use_count() << std::endl;
        }

    }


    line("end of main");

    return 0;
}