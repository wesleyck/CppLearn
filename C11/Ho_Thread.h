#ifndef _HO_THREAD_H
#define _HO_THREAD_H
#include <thread>

class Ho_Thread
{
protected:
  bool running_;
  std::thread *th_;
  void threadEntry();
  virtual void run() = 0;
public:
  Ho_Thread();
  virtual ~Ho_Thread();
  bool start();
  void stop();
  bool isAlive() const;
  void join(); // 等待当前线程结束，不能在当前线程上调用
  void detach(); // 能在当前线程上调用
  static size_t CURRENT_THREADID();

};

#endif

