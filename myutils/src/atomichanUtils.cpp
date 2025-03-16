#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <cmath>
#include <numeric>

template <typename T>
//void call_f(std::shared_ptr<A> myA)
void call_ff(std::shared_ptr<T> aClass)
{
    aClass->f();
}