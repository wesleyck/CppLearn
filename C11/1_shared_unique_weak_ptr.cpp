#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>
#include <string.h>

// thread 需要引入库，make_unique 需要c14  -lpthread -std=c++14

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

      // wrong，因为this本身裸指针，会double free
    // return std::shared_ptr<A1>(this); 
  }
  A1() {
    std::cout << "Construction A" << std::endl;
  }
  ~A1() {
    std::cout << "Destruction A" << std::endl;
  }
};

int main5() {
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


// 6.unique_ptr move 用法 删除器需要指定类型
struct MyDeleter {
  void operator()(int *p) {
    if (p) {
      std::cout << "delete function " << std::endl;
      delete p;
    }
  }
};

int main6() {
    std::cout << "Hello main 6" << std::endl;
    std::cout << "============" << std::endl;

    // auto up1(std::make_unique<int[]>(2)); // c14引入 make
    // std::unique_ptr<int> up2(new int);
    // up1[21] = 1;
    {
    std::unique_ptr<int, MyDeleter> up30(new int(1), MyDeleter());
    }
    // std::cout << "up 1: " << up1[20] << std::endl;

    std::unique_ptr<int> up1(new int);
    if (!up1) {
      std::cout << "unique_ptr 3 is null" << std::endl;
    }
    std::unique_ptr<int> up2 = std::move(up1);
    if (!up1) {
      std::cout << "unique_ptr 3 is null" << std::endl;
    }
    if (!up2) {
      std::cout << "unique_ptr3 is null" << std::endl;
    }
    
    // 不合法，unique可以数组初始化，而shared不行
    // std::shared_ptr<int []> sp1(new int[10]);
    std::unique_ptr<int []> up3(new int[10]);
    up3[9] = 9;
    // 编译不进行边界检查，直到运行才会报错（此时多分配的内存影响up5的分配，总之不要越界）
    //  很危险
    // up3[10] = 10; 
    std::cout << "up3[10]: " << up3[9] << std::endl;

    // auto up1(std::make_unique<int[]>(2));
    // wrong，unique_ptr 构造函数默认删除器，如果提供必须要指定类型，shared_ptr不用
    // std::unique_ptr<int> up4(new int(1), [](int *p){delete p;});
    // std::cout << "up4:  " << *up4 << std::endl;

    std::unique_ptr<int, void(*)(int*)> up5(new int(1), [](int *p){delete p;}); 
    std::cout << "up5:  " << *up5 << std::endl;

    std::cout << "============" << std::endl;
    std::cout << "main end!" << std::endl;
    return 0;
}



// 7.weak_ptr 用法和wrong 用例
std::weak_ptr<int> global_wp1;
void weak_f1() {
  auto spt = global_wp1.lock(); // 先锁好资源再去使用
  if (global_wp1.expired()) {
    std::cout << "global wp Invalid, resource release" << std::endl;

  } else {
    std::cout << "global wp Valid, *spt = " << *spt << std::endl;
  }
}

void weak_f2() {
  std::cout << "lock resources" << std::endl;
  auto spt = global_wp1.lock(); // 锁好资源再去判断，保证reset后还能用
  std::this_thread::sleep_for(std::chrono::seconds(2));
  if (global_wp1.expired()) {
    std::cout << "global weak Invalid, resource released" << std::endl;
  } else {
    std::cout << "global weak Valid, *spt = " << *spt << std::endl;
  }
}

void weak_f3() {
  std::cout << "========weak 3 test=======" << std::endl;
  std::weak_ptr<int> wp;
  {
    std::shared_ptr<int> sp(new int(1));
    std::cout << "before wp sp.use_count() = " << sp.use_count() << std::endl;
    wp = sp;
    std::cout << "after  wp sp.use_count() = " << sp.use_count() << std::endl;
  }
  std::shared_ptr<int> sp_null = wp.lock();
  if (!sp_null) {
    std::cout << "shared_ptr is null" << std::endl;
  }
  if (wp.expired()) {
    std::cout << "shared_ptr is destory" << std::endl;
  } else {
    std::cout << "shared_ptr no destory" << std::endl;
  }
}

void weak_f4() {
  std::cout << "========weak 4 test=======" << std::endl;
  std::weak_ptr<int> wp;
  std::shared_ptr<int> sp;
  {
    std::shared_ptr<int> sp1(new int(1));
    std::cout << "before wp sp.use_count() = " << sp1.use_count() << std::endl;
    wp = sp1;
    std::cout << "after  wp sp.use_count() = " << sp1.use_count() << std::endl;
    sp = wp.lock();
    std::cout << "after sp sp.use_count() = " << sp1.use_count() << std::endl;
  }
  // std::shared_ptr<int> sp_null = wp.lock();
  if (sp) {
    std::cout << "shared_ptr no destory sp" << std::endl;
  }
  if (wp.expired()) {
    std::cout << "shared_ptr is destory" << std::endl;
  } else {
    std::cout << "shared_ptr no destory" << std::endl;
  }
}

int main() {
  {
    auto sp = std::make_shared<int>(42);
    global_wp1 = sp;
    weak_f1();
  }
  weak_f1();

  {
    auto sp = std::make_shared<int>(42);
    global_wp1 = sp;
    std::thread([&](){
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "sp reset" << std::endl;
      sp.reset();
    }).detach();

    weak_f2();
  }

  weak_f3();

  weak_f4();
  return 0;
}