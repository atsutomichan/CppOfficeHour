#include <iostream>
#include "A.h"

class B : public A
{
    public:
    B(){}
    ~B(){}

    //void f();

    void f()
    {
        std::cout << "call derived function." << std::endl;
    }

    void f_alternative();
};