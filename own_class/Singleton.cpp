#include <_mingw_stat64.h>
//
// Created by ogier on 24-8-9.
//
#include <iostream>
class Singleton {
  public:
    Singleton(Singleton &other) = delete;
    void operator=(Singleton &other) = delete;
    static Singleton *get_instance(const int &val);
    int value() {
      return value_;
    }
    void do_something() {
      std::puts("do something");
    }

  public:
    Singleton(const int val): value_(val) {
    };
    static Singleton *singleton_;
    int value_;
};
Singleton *Singleton::singleton_ = nullptr;
Singleton *Singleton::get_instance(const int &val) {
  if (singleton_ == nullptr)
    return new Singleton(val);
  return singleton_;
}
