#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>
#include <string.h>

// error example
// 1.shared_ptr不能两次使用裸指针初始化,只能一次，否则double free
int main1() {
  std::cout << "Hello main 1!" << std::endl;
  {
    int *ptr = new int;
    std::shared_ptr<int> p1(ptr);
    // std::shared_ptr<int> p2(ptr); // wrong! 
    std::shared_ptr<int> p2(p1); // right 
  }

  std::cout << "main end!" << std::endl;
  return 0;
}


// 2. shared_ptr手动设置删除器 或者匿名函数
void DeleteIntPtr(int *p) {
  std::cout << "call DeleteIntPtr" << std::endl;
  delete p;
}
int main2() {
    std::cout << "Hello main 2" << std::endl;
    {
      std::shared_ptr<int> p1(new int(1), DeleteIntPtr);
      std::shared_ptr<int> p2(new int(2));
      std::shared_ptr<int> p3(new int(3), [](int *p){
        std::cout << "call lambda delete p2" << std::endl;
        delete p;});
      std::shared_ptr<int> p4(new int[10], [](int *p) {
        std::cout << "call lambda2 delete p4(array)" << std::endl;
        delete [] p;}); // 删除数组
      std::cout << p1.use_count() << std::endl;
    }

    std::cout << "main end!" << std::endl;
    return 0;
}


// 3.shared_ptr reset用法，作用域
void scope_test(std::shared_ptr<int> sp) {
  // test sp作用域
  std::cout << "test sp.use_count = " << sp.use_count() << std::endl;
}
int main3() {
    std::cout << "Hello main 3" << std::endl;
    std::cout << "============" << std::endl;

    auto sp1 = std::make_shared<int>(100); // 优先make，效率高
    std::shared_ptr<int> sp2(new int(100)); // =上

    // 不能将裸指针指向shared_ptr，指向对象不同
    // std::shared_ptr<int> sp3 = new int(1); 
    
    std::shared_ptr<int> sp3; 
    sp3.reset(new int(1)); // 分配资源
    if (sp3) {
      std::cout << "sp3 ptr new int(1)" << std::endl;
    }

    std::shared_ptr<int> sp4(sp3);
    std::shared_ptr<int> sp5 = sp4;
    // 引用计数3，相互赋值赋的是管理的同一对象
    std::cout << "sp3.use_count() = " << sp3.use_count() << std::endl;
    sp4.reset(); // 释放资源，同时执行的引用计数会少1
    // 0
    std::cout << "sp4.use_count() = " << sp4.use_count() << std::endl;
    // 2
    std::cout << "sp3.use_count() = " << sp3.use_count() << std::endl;

    if (!sp4) {
      std::cout << "sp4 after reset, null " << std::endl;
    }

    int* p = new int(10);
    std::shared_ptr<int> sp6(p);
    std::cout << "sp5.use_count() = " << sp5.use_count() << std::endl;

    std::shared_ptr<int> sp7(new int(20));
    // test传参过去增加引用次数1
    scope_test(sp7);
    // 返回时引用次数-1
    std::cout << "sp6.use_count() = " << sp7.use_count() << std::endl;

    std::cout << "=========" << std::endl;
    std::cout << "main end!" << std::endl;
    return 0;
}


// 4.循环引用计数问题，导致内存泄漏，可以使用weak_ptr解决
class A;
class B;
class A {
public:
  // 会导致循环引用计数问题，
  // std::shared_ptr<B> bptr; 
  std::weak_ptr<B> bptr; 
  ~A() {
    std::cout << "A is deleted" << std::endl;
  }
};

class B {
public:
  std::shared_ptr<A> aptr;
  ~B() {
    std::cout << "B is deleted" << std::endl;
  }
};

int main4() {
    std::cout << "Hello main 4" << std::endl;
    std::cout << "============" << std::endl;
    {
      std::shared_ptr<A> ap(new A);
      std::shared_ptr<B> bp(new B);
      ap->bptr = bp;
      bp->aptr = ap;
    }
    std::cout << "============" << std::endl;
    std::cout << "main end!" << std::endl;
    return 0;
}


// 5. 返回自身double free 问题
class A1 : public std::enable_shared_from_this<A1>{
// class A1 {
public:
  std::shared_ptr<A1> GetSelf() {
    return shared_from_this(); // 解决下面double free问题

      // 千万别这么干，因为this本身裸指针，会double free
    // return std::shared_ptr<A1>(this); 
  }
  A1() {
    std::cout << "Construction A" << std::endl;
  }
  ~A1() {
    std::cout << "Destruction A" << std::endl;
  }
};

int main() {
    std::cout << "Hello main 5" << std::endl;
    std::cout << "============" << std::endl;
    
    std::shared_ptr<A1> sp2;
    std::shared_ptr<A1> sp1(new A1);
    sp2 = sp1->GetSelf();
    // std::shared_ptr<A1> sp2 = sp1;

    std::cout << "sp1.use_count() = " << sp1.use_count() << std::endl;
    std::cout << "sp1.get " << sp1.get() << std::endl; 
    std::cout << "sp2.use_count() = " << sp2.use_count() << std::endl;
    std::cout << "sp2.get " << sp2.get() << std::endl; 
    std::cout << "============" << std::endl;
    std::cout << "main end!" << std::endl;
    return 0;
}

int main6() {
    std::cout << "Hello main 6" << std::endl;
    std::cout << "============" << std::endl;

    std::cout << "============" << std::endl;
    std::cout << "main end!" << std::endl;
    return 0;
}



