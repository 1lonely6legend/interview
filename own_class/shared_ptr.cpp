//
// Created by ogier on 24-8-4.
//
/*实现一个shared_ptr，参考https://csguide.cn/cpp/memory/shared_ptr.htm
要实现一个简化版本的 shared_ptr，需要考虑以下几点
- 在智能指针类中存储裸指针（raw pointer）和引用计数。
- 在构造函数中为裸指针和引用计数分配内存。
- 在拷贝构造函数和赋值操作符中正确地更新引用计数。
- 在析构函数中递减引用计数，并在引用计数为零时删除对象和引用计数。
*/
#include <iostream>
template<typename T>
class own_shared_ptr {
  public:
    //构造函数，注意使用explicit关键字，防止隐式转换
    //例如own_shared_ptr<int> p = new int(1);这种隐式转换是不允许的
    explicit own_shared_ptr(T *ptr = nullptr) {
      ptr_ = ptr;
      //如果传入的指针不为空，就为引用计数分配内存并初始化为1，否则初始化为空指针
      count_ = ptr ? new size_t(1) : nullptr;
    }
    //拷贝构造函数
    own_shared_ptr(const own_shared_ptr &other) {
      ptr_ = other.ptr_;
      count_ = other.count_;
      if (count_) {
        //注意自增运算符优先级高于解引用运算符，不能写成*count_++
        ++(*count_);
      }
    }
    //默认析构函数，调用release函数通过count_判断能否释放资源
    ~own_shared_ptr() {
      release();
    }
    //赋值操作符
    own_shared_ptr &operator=(const own_shared_ptr &other) {
      if (this != &other) {
        //如果不是自赋值
        release(); //首先释放当前对象
        ptr_ = other.ptr_;
        count_ = other.count_;
        if (count_) {
          //如果引用计数不为空，就更新引用计数
          ++(*count_);
        }
      }
      //返回当前对象的引用
      return *this;
    }
    //解引用操作符,返回引用
    T &operator*() const { return *ptr_; };
    //箭头操作符，返回指针
    T *operator->() const { return ptr_; };
    //获取裸指针
    T *get() const { return ptr_; };
    //获取引用计数，注意判断是否为空
    size_t use_count() const { return count_ ? *count_ : 0; };

  private:
    void release() {
      std::puts("try release");
      //如果引用计数不为空，然后递减引用计数，如果引用计数为0，就释放资源
      if (count_ && --(*count_) == 0) {
        delete ptr_;
        delete count_;
      }
    }
    T *ptr_;
    size_t *count_;
};

class Test {
  public:
    Test() { std::puts("constructor"); }
    ~Test() { std::puts("destructor"); }
    void do_something() { std::puts("do_something"); }
};
int main() {
  {
    own_shared_ptr<Test> ptr1(new Test());
    {
      own_shared_ptr<Test> ptr2 = ptr1;
      ptr1->do_something();
      ptr2->do_something();
      std::cout << "count: " << ptr1.use_count() << std::endl;
    } //ptr2调用默认析构
    std::cout << "count:  " << ptr1.use_count() << std::endl;
  }//ptr1调用默认析构
  int a = 1;
  return 0;
}
