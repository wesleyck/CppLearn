#include <iostream>

class Temp {
public:
  Temp() {
    std::cout << "默认构造 Temp(): " << this << std::endl;
  }
  ~Temp() {
    std::cout << "默认析构 ~Temp(): " << this << std::endl;
  }
  Temp(const Temp&) {
    std::cout << "拷贝构造 Temp(const Temp&)：" << this << std::endl;
  }
  Temp& operator=(const Temp&) {
    std::cout << "拷贝赋值构造 Temp& operator=(const Temp&): " << this << std::endl;
  }
  Temp(Temp&&) {
    std::cout << "移动构造 Temp(Temp&&)" << this << std::endl;
  }
  Temp& operator=(const Temp&&) {
    std::cout << "移动赋值构造 Temp& operator=(const Temp&&)" << this << std::endl;
  }
};

Temp CreateTemp() {
  Temp t1;
  return t1;
}

int main() {
  // 下面均为拷贝构造，=在初始化的时候不是赋值的含义而是执行初始化的意思
  // 写下Temp t1;就会进行初始化
  if (false) { 
    Temp t1;
    std::cout << "=========" << std::endl;
    Temp t2 = t1;
    std::cout << "=========" << std::endl;
    Temp t3(t1);
    std::cout << "=========" << std::endl;
    Temp t4{t1};
  }

  if (false) { // 拷贝赋值构造
    Temp t1;
    std::cout << "=========" << std::endl;
    Temp t2;
    std::cout << "=========" << std::endl;
    t2 = t1;
    std::cout << "=========" << std::endl;
  }

  if (false) {
    Temp t1 = CreateTemp(); // 需禁掉返回值优化: -fno-elide-constructors
    Temp t2;
    Temp t3(std::move(t2));
    Temp t4{std::move(t1)};
  }

  if (true) {
    Temp t;
    t = Temp();
    Temp t1, t2;
    t1 = std::move(t2);
  }

  return 0;
}