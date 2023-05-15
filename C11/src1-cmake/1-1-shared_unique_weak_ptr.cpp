#include <iostream>
#include <memory>
#include <functional>

int main(void) {

    std::cout << "Hello World! " << std::endl;
    {
        int* ptr = new int;
        std::shared_ptr<int> p1 = std::make_shared<int>();
        std::shared_ptr<int> p2 = p1; // 逻辑错误，作用域括号结束后会free两次
        std::cout << "p1 address: " << p1.use_count() << std::endl;
        std::cout << "p2 address: " << p1.use_count() << std::endl;
    }
    std::cout << "done!" <<  std::endl;

    return 0;
}