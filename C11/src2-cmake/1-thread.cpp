#include <thread>
#include <iostream>
using namespace std;

void threadFun(int &a) // 引用传递
{
  cout << "this is thread fun !" <<endl;
  cout <<" a = "<<(a+=10)<<endl;
}
int main()
{
  int x = 10;
  thread t1(threadFun, std::ref(x));
  cout << "got 1 \n" << endl; 
  // std::this_thread::sleep_for(std::chrono::seconds(2));
  thread t2(std::move(t1)); // t1 线程失去所有权
  cout << "got 2 \n" << endl; 
  thread t3;
  cout << "got 3 \n" << endl; 
  t3 = std::move(t2); // t2 线程失去所有权
  //t1.join(); // ？
  cout << "got 4 \n" << endl; 
  t3.join();
  cout << "got 5 \n" << endl; 
  cout<<"Main End "<<"x = "<<x<<endl;
  return 0;
}
