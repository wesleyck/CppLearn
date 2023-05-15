#include <string>

class Context {
public:
    std::string name;
    int day;
};

// 稳定点 抽象  变化点 扩展 （多态）
//  从单个处理节点出发，我能处理，我处理，我不能处理交给下一个人处理
//  链表关系如何抽象

class IHandler {
public:
    virtual ~IHandler() : next(nullptr) {}
    void SetNextHandler(IHandler *next) { // 链表关系
        next = next;
    }
    bool Handle(const Context &ctx) {
        if (CanHandle(ctx)) {
            return HandleRequest(ctx);
        } else if (GetNextHandler()) {
            return GetNextHandler()->Handle(ctx);
        } else {
            // err
        }
        return false;
    }
    // 通过函数来抽象 处理节点的个数  处理节点顺序
    static bool handler_leavereq(Context &ctx) {
        IHandler * h0 = new HandleByBeauty();
        IHandler * h1 = new HandleByMainProgram();
        IHandler * h2 = new HandleByProjMgr();
        IHandler * h3 = new HandleByBoss();
        h0->SetNextHandler(h1);
        h1->SetNextHandler(h2);
        h2->SetNextHandler(h3);
        return h0->Handle(ctx);
    }
protected:
    virtual bool HandleRequest(const Context &ctx) {return true};
    virtual bool CanHandle(const Context &ctx) {return true};
    IHandler * GetNextHandler() {
        return next;
    }
private:
    IHandler *next; // 组合基类指针
};

// 能不能处理，以及怎么处理
class HandleByMainProgram : public IHandler {
protected:
    virtual bool HandleRequest(const Context &ctx){
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx) {
        //
        if (ctx.day <= 10)
            return true;
        return false;
    }
};

class HandleByProjMgr : public IHandler {
protected:
    virtual bool HandleRequest(const Context &ctx){
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx) {
        //
        if (ctx.day <= 20)
            return true;
        return false;
    }
};
class HandleByBoss : public IHandler {
protected:
    virtual bool HandleRequest(const Context &ctx){
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx) {
        //
        if (ctx.day < 30)
            return true;
        return false;
    }
};

class HandleByBeauty : public IHandler {
protected:
    virtual bool HandleRequest(const Context &ctx){
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx) {
        //
        if (ctx.day <= 3)
            return true;
        return false;
    }
};

int main() {
    // IHandler * h1 = new HandleByMainProgram();
    // IHandler * h2 = new HandleByProjMgr();
    // IHandler * h3 = new HandleByBoss();
    // h1->SetNextHandler(h2);
    // h2->SetNextHandler(h3);
// 抽象工厂
// nginx http 处理 
    // 设置下一指针 
    Context ctx;
    if (IHander::handler_leavereq(ctx)) {
        cout << "请假成功";
    } else {
        cout << "请假失败";
    }
    
    return 0;
}