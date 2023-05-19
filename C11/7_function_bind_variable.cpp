#include <iostream>
#include <functional> // 添加头文件 functional
using namespace std;

// function 类似c的函数指针
//保存普通函数
void func1(int a)
{
     cout << a << endl;
}
//保存成员函数
class A{
public:
    A(string name) : name_(name){}
    void func3(int i) const {cout <<name_ << ", " << i << endl;}
    // void func3(string str) const {cout <<name_ << ", " << str << endl;}

    //    std::bind((void(A::*)(int, int))&A::fun_4
    void func4(int k,int m)
    {
        cout<<"func4 print: k="<<k<<",m="<<m<<endl;
    }
//    std::bind((void(A::*)(string))&A::fun_4
    void func4(string str) {
        cout<<"func4 print: str="<<str<<endl;
    }
private:
    string name_;
};
int main1()
{
  cout << "main1 -----------------" << endl;
  //1. 保存普通函数
  std::function<void(int a)> func1_;
  func1_ = func1;
  func1_(2);   //2

    cout << "\n\nmain2 -----------------" << endl;
  //2. 保存lambda表达式
  std::function<void()> func2_ = [](){cout << "hello lambda" << endl;};
  func2_();  //hello world

  cout << "\n\nmain3 -----------------" << endl;
  //3 保存成员函数
  std::function<void(const A&, int)> func3_ = &A::func3;
  A a("darren");
  func3_(a, 1);

  //4.重载函数
  std::function<void(int, int)> func4_1 = std::bind((void(A::*)(int, int))&A::func4, a, std::placeholders::_1, std::placeholders::_2); 
  func4_1(1,2);
  auto f_str = std::bind((void(A::*)(string))&A::func4, a, std::placeholders::_1);
  f_str("darren");
  std::function<void(string)> f_str2 = std::bind((void(A::*)(string))&A::func4, &a, std::placeholders::_1);
  f_str2("kun");

  return 0;
}

// 2. bind 及重载

class A_1
{
public:
    // 重载fun_3，主要bind的时候需要
//    std::bind((void(A::*)(int, int))&A::fun_3
    void fun_3(int k,int m)
    {
        cout << "fun_3 a = " << a<< endl;
        cout<<"print: k="<<k<<",m="<<m<<endl;
    }
//    std::bind((void(A::*)(string))&A::fun_3
    void fun_3(string str) {
        cout<<"print: str="<<str<<endl;
    }
    int a;
};

void fun_1(int x, int y, int z)
{
  cout<<"fun_1 print: x=" <<x<<",y="<< y << ",z=" <<z<<endl;
}

void fun_2(int &a, int &b)
{
  a++;
  b++;
  cout << "print: a=" << a << ",b=" << b << endl;
}

void func2_1(int a, int b)
{
    cout << "func2_1 a + b = " << a+b << endl;
}

int func2_1(string a, string b)
{
    cout << "func2_1 a + b = " << a << b<< endl;
    return 0;
}

int main2()
{
  // f1 类型function<void(int, int, int)>
  std::cout << "------function f1 bind------"<< std::endl;
  auto f1 = std::bind(fun_1, 1, 2, 3); // 固定绑定参数
  f1();

  // 占位符的序号表示fun中的序号，有实际参数则固定位置
  std::cout << "------function f2 bind placeholder ------"<< std::endl;
  auto f2 = std::bind(fun_1, std::placeholders::_1,  std::placeholders::_2, 3); // 绑定最后一个
  // f2();
  f2(1, 2, 4);
  f2(1, 2); // 1 2 3
  f2(2, 1, 4, 4); 
  auto f3 = std::bind(fun_1, std::placeholders::_2,  std::placeholders::_1, 3); // 绑定最后一个
  // f3();
  f3(1, 2, 4);
  f3(1, 2); // 2 1 3
  f3(2, 1, 4, 3); // 2 1 3

  cout << "bind first 2 " <<std::endl;
  auto f4 = std::bind(fun_1, 2, std::placeholders::_2, std::placeholders::_1); 
  f4(3, 4); // 2 4 3

  cout << "\n\nstd::bind(fun_2, placeholders::_1, n) -----------------\n";
  int m = 2;
  int n = 3;
  auto f5 = std::bind(fun_2, placeholders::_1, n); //表示绑定fun_2的第一个参数为n, fun_2的第二个参数由调用f4的第一个参数（_1）指定。
  f5(m); //print: m=3,n=4
  cout << "m = " << m << endl; //说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的,如m
  cout << "n = " << n << endl; //说明：bind对于预先绑定的函数参数是通过值传递的，如n

  cout << "\n\nstd::bind(&A::fun_3, &a,placeholders::_1,placeholders::_2) -----------------\n";
  A_1 a;
  a.a = 10;
  // 重载类型
  auto f6 = std::bind((void(A_1::*)(int, int))&A_1::fun_3, &a, 10, 20);
  auto f7 = std::bind((void (A_1::*)(std::string))&A_1::fun_3, &a, " world");
  f6();
  f7();
  auto f8 = std::bind((void(A_1::*)(int, int))&A_1::fun_3, &a, std::placeholders::_1, std::placeholders::_2);
  f8(2, 3);
  int p = 10;
  auto f9 = std::bind((void(A_1::*)(int, int))&A_1::fun_3, &a, p, std::placeholders::_1);
  f9(22, 3);
  return 0;
}



// 3. 可变参数
template <class... T>
void f(T... args) {
    cout << sizeof...(args) << std::endl;
}

template <class F, class... Args> void expand(const F& f, Args&&... args) {
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}
int main() {
    // f();
    // f(1, 2);
    // f(1, 2.3, "");
    expand([](int i) {cout << i << endl;}, 3,5,7);

    return 0;
}

