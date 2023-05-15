#include <list>
#include <algorithm>
using namespace std;
//
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
            iter.Show(temper);
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
    center->Attach(dd);

    center->Notify();
    return 0;
}