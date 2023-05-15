#include <iostream>
using namespace std;

// 设计原则
// 1. 设计原则演变过来的  2.符合设计原则的代码，只需要修改少量代码就可以演变成设计模式
// 接口隔离原则  1. 类封装 权限限定词来实现 2. 类与类依赖 接口（依赖注入）
// 最小知道原则
// 破坏了哪些设计原则：
// 单一职责（变化方向） 封装
// 开闭原则 对扩展开放 对修改关闭
// 扩展方式：继承，多态组合
class ZooShow {
public:
    ZooShow(int type = 1) : _type(type) {}

public:
    void Show() {
        if (Show0())
            PlayGame();
        Show1();
        Show2();
        Show3();
    }

private:
    void PlayGame() {
        cout << "after Show0, then play game" << endl;
    }

    bool Show0() {
        if (_type == 1) {
            // 
            return true;
        } else if (_type == 2 ) {
            //  ...
        } else if (_type == 3) {

        }
        cout << _type << " show0" << endl;
        return true;
    }

    void Show1() {
        if (_type == 1) {
            cout << _type << " Show1" << endl;
        } else if (_type == 2) {
            cout << _type << " Show1" << endl;
        } else if (_type == 3) {

        }
    }

    void Show2() {
        if (_type == 20) {
            
        }
        cout << "base Show2" << endl;
    }

    void Show3() {
        if (_type == 1) {
            cout << _type << " Show1" << endl;
        } else if (_type == 2) {
            cout << _type << " Show1" << endl;
        }
    }
private:
    int _type;
};


int main () {
    ZooShow *zs = new ZooShow(1);
    zs->Show();
    return 0;
}
