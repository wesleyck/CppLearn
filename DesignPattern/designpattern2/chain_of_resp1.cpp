#include <string>

class Context {
public:
    std::string name;
    int day;
};

class LeaveRequest {
public:
    bool HandleRequest(const Context &ctx) {
        if (ctx.day <= 1)
            HandleByBeaty(ctx);
        if (ctx.day <= 1)
            HandleByMainProgram(ctx);
        else if (ctx.day <= 10)
            HandleByProjMgr(ctx);
        else
            HandleByBoss(ctx);
    }

private:
    bool HandleByBeaty(const Context &ctx) {
        
    }
    bool HandleByMainProgram(const Context &ctx) {
        
    }
    bool HandleByProjMgr(const Context &ctx) {
        
    }
    bool HandleByBoss(const Context &ctx) {

    }
};