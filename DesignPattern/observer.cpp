#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

class IDisplay {
public:
    virtual void Show(float temperature) = 0;
    virtual ~IDisplay() {}
};

class DisplayA : public IDisplay {
public:
    virtual void Show(float temperature) {
        cout << "DisplayA Show" << endl;
    }
private:
    void jianyi();
};

class DisplayB : public IDisplay{
public:
    virtual void Show(float temperature) {
        cout << "DisplayB Show" << endl;
    }
};

class DisplayC : public IDisplay{
public:
    virtual void Show(float temperature) {
        cout << "DisplayC Show" << endl;
    }
};

class DisplayD : public IDisplay{
public:
    virtual void Show(float temperature) {
        cout << "DisplayC Show" << endl;
    }
};

class WeatherData {
};

// 应对稳定点，抽象
// 应对变化点，扩展（继承和组合）
class DataCenter {
public:
    void Attach(IDisplay * ob) {
        //
    }
    void Detach(IDisplay * ob) {
        //
    }
    void Notify() {
        float temper = CalcTemperature();
        for (auto iter : obs) {
            iter->Show(temper);
        }
    }

// 接口隔离
private:
    WeatherData * GetWeatherData();

    float CalcTemperature() {
        WeatherData * data = GetWeatherData();
        // ...
        float temper/* = */;
        return temper;
    }
    std::list<IDisplay*> obs;
};

int main() {
    // 单例模式
    DataCenter *center = new DataCenter;
    // ... 某个模块
    IDisplay *da = new DisplayA();
    center->Attach(da);

    // ...
    IDisplay *db = new DisplayB();
    center->Attach(db);
    
    IDisplay *dc = new DisplayC();
    center->Attach(dc);

    center->Notify();
    
    //-----
    center->Detach(db);
    center->Notify();


    //....
    IDisplay *dd = new DisplayD();
    center->Attach(dd);

    center->Notify();
    return 0;
}



// 耦合太紧密，需要修改类结构才能拓展，极其不方便
#if 0

class DisplayA {
public:
    void Show(float temperature);
};

class DisplayB {
public:
    void Show(float temperature);
};

class DisplayC {
public:
    void Show(float temperature);
};

class WeatherData {
};

class DataCenter {
public:
    void TempNotify() {
        DisplayA *da = new DisplayA;
        DisplayB *db = new DisplayB;
        DisplayC *dc = new DisplayC;
        // DisplayD *dd = new DisplayD;
        float temper = this->CalcTemperature();
        da->Show(temper);
        db->Show(temper);
        dc->Show(temper);
        dc->Show(temper);
    }
private:
    float CalcTemperature() {
        WeatherData * data = GetWeatherData();
        // ...
        float temper/* = */;
        return temper;
    }
    WeatherData * GetWeatherData(); // 不同的方式
};

int main() {
    DataCenter *center = new DataCenter;
    center->TempNotify();
    return 0;
}

#endif
