#include <iostream>

using namespace std;

class T {
public:
    T() {
        cout << "T():" << this << endl;
    }
    ~T() {
        cout << "~T():" << this << endl;
    }
    T(const T&) {
        cout << "T(const T&) 拷贝构造:" << this << endl;
    }
    T& operator=(const T&) {
        cout << "T& operator=(const T&) 拷贝赋值构造:" << this << endl;
    }
    T(T &&) {
        cout << "T(T &&) 移动构造:" << this << endl;
    }
    T& operator=(T&&) {
        cout << "T& operator=(T&&) 移动赋值构造:" << this << endl;
    }
};

T CreateT() {
    T temp;
    return temp;
}

int main() {
    if (false) { // 拷贝构造
        T t1;
        T t2 = t1;
        //========
        T t3(t1);
        //========
        T t4{t1};
    }
    if (false) { // 拷贝赋值构造
        T t1;
        T t2;
        t1 = t2;
    }
    if (false) { // 移动构造
        // *禁掉返回值优化: -fno-elide-constructors
        T t = CreateT();
        
        T t1;
        T t2(std::move(t1));
    }
    if (false) { // 移动赋值构造
        T t;
        t = T();
        
        T t1, t2;
        t1 = std::move(t2);
    }
    return 0;
}