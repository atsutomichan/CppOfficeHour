#include <memory>
#include <atomichanUtils.h>
#include <A.h>


//template <typename T>
//void call_ff(std::shared_ptr<T> aClass)
void call_f(std::shared_ptr<A> aClass)
{
    aClass->f();
}