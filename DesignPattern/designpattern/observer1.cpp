
// 耦合太紧密，需要修改类结构才能拓展，极其不方便
#if 1

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
