#include <iostream>
#include <memory>
#include <A.h>
#include <B.h>

void call_f(std::shared_ptr<A> myA)
{
    myA->f();
}


int main()
{
    std::shared_ptr<B> my_B_ptr = std::make_shared<B>();

    call_f(my_B_ptr);
    return 0;
}

/*
class A
{
    public:
    A(){}
    ~A(){}

    virtual void f() = 0;
};

class B : public A
{
    public:
    B(){}

    void f()
    {
        std::cout << "call derived function." << std::endl;
    }
};
*/