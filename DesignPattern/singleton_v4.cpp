#include <mutex>
#include <atomic>

class  Singleton {
public:
    static Singleton* getInstance() {
        // 原子变量解决原子性 可见性 执行序
        Singleton* tmp = _instance.load(std::memory_order_acquire);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(_mutex);
            tmp = _instance.load(std::memory_order_acquire);
            if (tmp == nullptr) {
                tmp = new Singleton;
                _instance.store(tmp, std::memory_order_release);
                atexit(Destruct);
            }
        }

        return tmp;
    }

private:
    std::atomic<Singleton*> Singleton::_instance;
    std::mutex Singleton::_mutex;
    
}