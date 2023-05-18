#include "Ho_Thread.h"
#include <iostream>
#include <exception>
#include <sstream>

Ho_Thread::Ho_Thread() : running_(false), th_(nullptr)
{

}

Ho_Thread::~Ho_Thread()
{
  if(th_ != nullptr) {
    if (th_->joinable()) {
      // 如果到析构的时候，调用者还没有调用join，则触发detach，会比较危险，要明确当前行为
      std::cout << "~Ho_Thread detach" << std::endl;
      th_->detach();
    }
    delete th_;
    th_ = nullptr;
  }
  std::cout << "~Ho_thread()" << std::endl;
}

bool Ho_Thread::start() {
  if (running_) {
    return false;
  }
  try
  {
    th_ = new std::thread(&Ho_Thread::threadEntry, this);
  }
  catch(const std::exception& e)
  {
    throw "[Ho_Thread:start] thread start error";
    // std::cerr << e.what() << '\n';
  }
  return true;
}

void Ho_Thread::stop() {
  running_ = false;
}

bool Ho_Thread::isAlive() const{
  return running_;
}

void Ho_Thread::join() {
  if (th_->joinable()) {
    th_->join(); // 非deatch才去join
  }
}

void Ho_Thread::detach() {
  th_->detach();
}

size_t Ho_Thread::CURRENT_THREADID() {
  // thread_local 本地变量生命周期等同线程
  static thread_local size_t threadId = 0;
  if (threadId == 0) {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    threadId = strtol(ss.str().c_str(), nullptr, 0); 
  }
  return threadId;
} 

void Ho_Thread::threadEntry() {
  running_ = true;

  try
  {
    run(); // 函数运行所在，调用子类的run函数
  }
  catch(const std::exception& e)
  {
    running_ = false;
    std::cerr << e.what() << '\n';
  }
  catch (...) 
  {
    running_ = false;
    throw ;
  }
  running_ = false;
  
}
