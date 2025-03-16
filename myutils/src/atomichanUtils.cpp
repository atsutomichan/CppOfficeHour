#include <memory>
#include <A.h>
#include <atomichanUtils.h>


//template <typename T>
void call_f(std::shared_ptr<A> aClass)
//void call_ff(std::shared_ptr<T> aClass)
{
    aClass->f();
}