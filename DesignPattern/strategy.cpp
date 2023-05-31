class Context {

};

// 稳定点：抽象去解决它
// 变化点：扩展（继承和组合）去解决它
class ProStategy {
public:
    virtual double CalcPro(const Context &ctx) = 0;
    virtual ~ProStategy(); 
};
// cpp
class VAC_Spring : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_QiXi : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
class VAC_QiXi1  : public VAC_QiXi {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_Wuyi : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_GuoQing : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class VAC_Shengdan : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class Promotion {
public:
    Promotion(ProStategy *sss) : s(sss){}
    ~Promotion(){}
    double CalcPromotion(const Context &ctx){
        return s->CalcPro(ctx);
    }
private:
    ProStategy *s;
};

int main () {
    Context ctx;
    ProStategy *s = new VAC_QiXi1();
    Promotion *p = new Promotion(s);
    p->CalcPromotion(ctx);
    return 0;
}

#if 0
enum VacationEnum {
	VAC_Spring,
    VAC_QiXi,
	VAC_Wuyi,
	VAC_GuoQing,
    VAC_ShengDan,
};

class Promotion {
    VacationEnum vac;
public:
    double CalcPromotion(){
        if (vac == VAC_Spring) {
            // 春节
        }
        else if (vac == VAC_QiXi) {
            // 七夕
        }
        else if (vac == VAC_Wuyi) {
            // 五一
        }
		else if (vac == VAC_GuoQing) {
			// 国庆
		}
        else if (vac == VAC_ShengDan) {

        }
     }
    
};
#endif