//
// Created by ogier on 24-8-9.
//
#include <iostream>

#include <iostream>

class MyClass {
  public:
    int value;

    // 构造函数
    MyClass(int v) : value(v) {
      std::cout << "构造函数被调用，value = " << value << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass &other) : value(other.value) {
      std::cout << "拷贝构造函数被调用，value = " << value << std::endl;
    }

    // 拷贝赋值运算符
    MyClass &operator=(const MyClass &other) {
      if (this == &other) {
        return *this; // 处理自我赋值。
      }
      value = other.value;
      std::cout << "拷贝赋值运算符被调用，value = " << value << std::endl;
      return *this;
    }

    // 移动构造函数
    MyClass(MyClass &&other) noexcept : value(other.value) {
      other.value = 0; // 将源对象的value设为0以表示资源已被移动
      std::cout << "移动构造函数被调用，value = " << value << std::endl;
    }

    // 移动赋值运算符
    MyClass &operator=(MyClass &&other) noexcept {
      if (this == &other) {
        return *this; // 处理自我赋值
      }
      value = other.value;
      other.value = 0; // 将源对象的value设为0以表示资源已被移动
      std::cout << "移动赋值运算符被调用，value = " << value << std::endl;
      return *this;
    }

    // 析构函数
    ~MyClass() {
      std::cout << "析构函数被调用，value = " << value << std::endl;
    }
};

// 一个函数，返回一个MyClass对象，产生一个右值
MyClass createObject(int v) {
  return MyClass(v);
}

int main() {
  MyClass obj1(10); // 调用构造函数
  MyClass obj2 = obj1; // 调用拷贝构造函数（左值）
  MyClass obj3(20); // 调用构造函数
  obj3 = obj1; // 调用拷贝赋值运算符（左值）

  MyClass obj4 = createObject(30); // 调用移动构造函数（右值）
  obj3 = createObject(40); // 调用移动赋值运算符（右值）

  return 0; // 所有对象会在此点析构，调用析构函数
}
