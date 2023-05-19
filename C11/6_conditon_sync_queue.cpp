#include <iostream>
#include <mutex>
#include <condition_variable>
#include <list>
#include <thread>
#include <atomic>  
#include <future>

using namespace std;

// 1. 同步队列 wait(lock, bool) 提供谓词，防止虚假唤醒
template<typename T>
class SimpleSyncQueue
{
public:
    SimpleSyncQueue(){}

    void Put(const T& x)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        _queue.push_back(x);
        _notEmpty.notify_one();
    }

    void Take(T& x)
    {
        std::unique_lock<std::mutex> locker(_mutex);
        _notEmpty.wait(locker, [this]{return !_queue.empty(); });

        x = _queue.front();
        _queue.pop_front();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.empty();
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size();
    }

private:
    std::list<T> _queue;
    std::mutex _mutex;
    std::condition_variable _notEmpty;
};


SimpleSyncQueue<int> simplesyncQueue;
void PutDatas_0()
{
    for (int i = 0; i < 20; ++i)
    {
        // std::cout << "Put data : " << i << std::endl;
        simplesyncQueue.Put(i);
    }
}

void TakeDatas_0()
{
    int x = 0;
    for (int i = 0; i < 20; ++i)
    {
        simplesyncQueue.Take(x);
        std::cout << x << std::endl;
    }
}

int main1(void)
{
    std::thread t1(PutDatas_0);
    std::thread t2(TakeDatas_0);

    t1.join();
    t2.join();

    std::cout << "main finish\n";
    return 0;
}



// 2. 同步队列，手动采取判断，防止虚假唤醒，设置最大size
template<typename T>
class SyncQueue
{
private:
    bool IsFull() const
    {
        return _queue.size() == _maxSize;
    }

    bool IsEmpty() const
    {
        return _queue.empty();
    }

public:
    SyncQueue(int maxSize) : _maxSize(maxSize)
    {
    }

    void Put(const T& x)
    {
        // std::lock_guard<std::mutex> locker(_mutex);

        while (IsFull())
        {
            std::cout << "full wait... size " << _queue.size()  << std::endl;
            _notFull.wait(_mutex);
        }

        _queue.push_back(x);
        _notEmpty.notify_one();
    }

    void Take(T& x)
    {
        // std::lock_guard<std::mutex> locker(_mutex);

        while (IsEmpty())
        {
            std::cout << "empty wait.." << std::endl;
            _notEmpty.wait(_mutex);
        }

        x = _queue.front();
        _queue.pop_front();
        _notFull.notify_one();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.empty();
    }

    bool Full()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size() == _maxSize;
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size();
    }

    int Count()
    {
        return _queue.size();
    }

private:
    std::list<T> _queue;                  //缓冲区
    std::mutex _mutex;                    //互斥量和条件变量结合起来使用
    std::condition_variable_any _notEmpty;//不为空的条件变量
    std::condition_variable_any _notFull; //没有满的条件变量
    int _maxSize;                         //同步队列最大的size
};

SyncQueue<int> syncQueue(5);

void PutDatas()
{
    for (int i = 0; i < 20; ++i)
    {
        syncQueue.Put(i);
    }
    std::cout << "PutDatas finish\n";
}

void TakeDatas()
{
    int x = 0;

    for (int i = 0; i < 20; ++i)
    {
        syncQueue.Take(x);
        std::cout << x << std::endl;
    }
    std::cout << "TakeDatas finish\n";
}

int main2()
{
    std::thread t1(PutDatas);  // 生产线程
    std::thread t2(TakeDatas); // 消费线程

    t1.join();
    t2.join();

    std::cout << "main finish\n";
    return 0;
}



// 3. atomic 
std::atomic<int> count_ato(0);
void set_count (int x) {
    count_ato.store(x, std::memory_order_relaxed);    
    std::cout << "set count " << x <<  std::endl;
}

void print_count() {
    int x;
    do {
        x = count_ato.load(std::memory_order_relaxed);
    } while (x == 0);
    std::cout << "print count " << x << std::endl;
}
int main3() {
    int value = 10;
    std::thread t1(set_count, value);
    std::thread t2(print_count);
    t1.join();
    t2.join();

    return 0;
}



// 4. 异步操作 async future
int result_add() {
    int a = 3;
    int b = 4;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "-------result add---------" << std::endl;
    return a + b;
}

int result_add_2(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "-------result add---------" << std::endl;
    return a + b;
}

void do_something() {
    std::cout << "do something " << std::endl;
}

int main4() {
    auto result = std::async(result_add);

    std::future<int> result2 = std::async(result_add_2, 5, 5);
    std::future<decltype(result_add_2(0, 0))> result3 = std::async(result_add_2, 10, 20);
    do_something();

    std::cout << "get future result: " << result.get() << std::endl;
    std::cout << "get future result2: " << result2.get() << std::endl;
    return 0;
}



// 5. packaged_task
int add(int a, int b, int c)
{
    std::cout << "call add\n";
    return a + b + c;
}

void do_other_things()
{
    std::cout << "do_other_things" << std::endl;
}

int main5()
{
    std::packaged_task<int(int, int, int)> task(add);  // 1. 封装任务，还没有运行
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 用来测试异步延迟的影响

    do_other_things();
    std::future<int> result = task.get_future(); // 这里运行吗？这里只是获取 future
    // 这里才真正运行
    task(1, 1, 2);   //必须要让任务执行，否则在get()获取future的值时会一直阻塞
    std::cout << "result:" << result.get() << std::endl;
    return 0;
}



// 6. promise
void print1(std::promise<std::string>& p)
{
    std::cout << "print1 sleep" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value("set string"); // 返回future的结果
}

void print2(std::promise<int>& p)
{
    std::cout << "print2 sleep" << std::endl;
    p.set_value(1);
}

void do_some_other_things()
{
    std::cout << "do_some_other_things" << std::endl;
}

int main()
{
    std::cout << "main1 -------------" << std::endl;
    std::promise<std::string> promise;  // 注意类型:

    std::future<std::string> result = promise.get_future(); // future

    std::thread t(print1, std::ref(promise));  // 线程设置 传引用std::ref
    do_some_other_things();
    std::cout << "wait get result" << std::endl;
    std::cout <<"result " << result.get() << std::endl; // 在主线程等待 promise的返回 result set string
    t.join();


    std::cout << "\n\nmain2 -------------" << std::endl;
    std::promise<int> promise2;

    std::future<int> result2 = promise2.get_future();
    std::thread t2(print2, std::ref(promise2));
    do_some_other_things();
    std::cout << "result2 " << result2.get() << std::endl;
    t2.join();

    return 0;
}

