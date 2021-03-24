
#include <boost/bind/bind.hpp>
#include <functional>
#include <iostream>


void print(const int i)
{
  std::cout << "Int: " << i << std::endl;
}



class CallableObject
{
  public:
    CallableObject()
    {
      std::cout << "CallableObject created" << std::endl;
    }

    ~CallableObject()
    {
      std::cout << "CallableObject destroyed" << std::endl;
    }

    void print(const int i)
    {
      std::cout << "print called with " << i << std::endl;
    }

    void operator()(const int i)
    {
      std::cout << "CallableObject called " << i << std::endl;
    }
};


int main()
{
  std::cout << "Using boost::bind" << std::endl;
  const auto f1 = boost::bind(&print, 10);
  f1();

  std::cout << std::endl << "Using std::bind should be the same..." << std::endl;
  const auto f2 = std::bind(&print, 10);
  f2();

  std::cout << std::endl << "Arguments are copied, as the value of int i changes the copied int does not..." << std::endl;
  int i = 5;
  const auto f3 = std::bind(&print, i);
  f3();
  i = 6;
  f3();

  std::cout << std::endl << "However, by using std::ref a reference is bound instead of a copy and changes will be observed..." << std::endl;
  const auto f4 = std::bind(&print, std::ref(i));
  f4();
  i = 7;
  f4();

  std::cout << std::endl << "Binding to method in object..." << std::endl;
  CallableObject ca;
  ca(i);
  const auto f5 = std::bind(&CallableObject::print, &ca, i);
  f5();
/*
  std::function<void(const int)> mf = ca;
  const auto f6 = std::bind(mf, i);
  f6();
  */
}
