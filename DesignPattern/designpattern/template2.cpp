#include <iostream>
using namespace std;

// 开闭
class ZooShow {
public:
    void Show() {
        // 如果子表演流程没有超时的话，进行一个中场游戏环节；如果超时，直接进入下一个子表演流程
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
    bool expired;
    // 对其他用户关闭，但是子类开放的
protected:
    virtual bool Show0() {
        cout << "show0" << endl;
        if (! expired) {
            return true;
        }
        return false;
    }
    virtual void Show2() {
        cout << "show2" << endl;
    }
    virtual void Show1() {

    }
    virtual void Show3() {

    }
};

// 框架
// 模板方法模式
class ZooShowEx10 : public ZooShow {
protected:
    virtual void Show0() {
        if (! expired) {
            return true;
        }
        return false;
    }
}

class ZooShowEx1 : public ZooShow {
protected:
    virtual bool Show0() {
        cout << "ZooShowEx1 show0" << endl;
        if (! expired) { // 里氏替换
            return true;
        }
        return false;
    }
    virtual void Show2(){
        cout << "show3" << endl;
    }
};

class ZooShowEx2 : public ZooShow {
protected:
    virtual void Show1(){
        cout << "show1" << endl;
    }
    virtual void Show2(){
        cout << "show3" << endl;
    }
};

class ZooShowEx3 : public ZooShow {
protected:
    virtual void Show1(){
        cout << "show1" << endl;
    }
    virtual void Show3(){
        cout << "show3" << endl;
    }
    virtual void Show4() {
        //
    }
};
/*
*/
int main () {
    ZooShow *zs = new ZooShowEx10; // 晚绑定还是早绑定
    // ZooShow *zs1 = new ZooShowEx1;
    // ZooShow *zs2 = new ZooShowEx2;
    zs->Show();
    return 0;
}

