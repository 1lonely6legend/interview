//
// Created by ogier on 24-4-29.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <cmath>
#include <numeric>
using namespace std;

//线程要做的事情就写在这个线程函数中
//cpp中的线程函数只能返回void类型，常常使用传递引用的方式返回结果
void GetSumT(vector<int>::iterator first,vector<int>::iterator last,int &result)
{
  result = accumulate(first,last,0); //调用C++标准库算法,最后一个参数是初始值
}

int main() //主线程
{
  int result1,result2,result3,result4,result5;
  vector<int> largeArrays;
  for(int i=0;i<100000000;i++) {
    if(i%2==0)
      largeArrays.push_back(i);
    else
      largeArrays.push_back(-1*i);
  }
  //thread类的构造函数，第一个参数是线程函数，后面的参数是线程函数的参数
  //如果参数中有引用，需要使用std::ref()函数，不能直接传递引用
  thread first(GetSumT,largeArrays.begin(),largeArrays.begin()+200000,std::ref(result1)); //子线程1
  thread second(GetSumT,largeArrays.begin()+20000000, largeArrays.begin()+40000000,std::ref(result2)); //子线程2
  thread third(GetSumT,largeArrays.begin()+40000000,largeArrays.begin()+60000000,std::ref(result3)); //子线程3
  thread fouth(GetSumT,largeArrays.begin()+60000000,largeArrays.begin()+80000000,std::ref(result4)); //子线程4
  thread fifth(GetSumT,largeArrays.begin()+80000000, largeArrays.end(),std::ref(result5)); //子线程5

  //join()是一个阻塞函数，主线程会等待子线程执行完毕，意味着主线程和子线程同步
  //主线程要等待子线程执行完毕
  first.join();
  second.join();
  third.join();
  fouth.join();
  fifth.join();
  cout << "result1: " << result1 << endl;
  cout << "result2: " << result2 << endl;
  cout << "result3: " << result3 << endl;
  cout << "result4: " << result4 << endl;
  cout << "result5: " << result5 << endl;
  int resultSum = result1+result2+result3+result4+result5; //汇总各个子线程的结果
  cout<<"Sum of largeArrays: "<<resultSum<<endl;
  return 0;
}