#include <iostream>
#include <mutex>
#include <condition_variable>
#include <list>
#include <thread>

using namespace std;

// 1. 同步队列
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

int main(void)
{
    std::thread t1(PutDatas_0);
    std::thread t2(TakeDatas_0);

    t1.join();
    t2.join();

    std::cout << "main finish\n";
    return 0;
}




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

int main1(void)
{
    std::thread t1(PutDatas);  // 生产线程
    std::thread t2(TakeDatas); // 消费线程

    t1.join();
    t2.join();

    std::cout << "main finish\n";
    return 0;
}


