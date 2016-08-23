
#pragma once

#include "Common.h"
#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F, typename... Args>
double profileFunc(F func, Args&&... args){
    TimeVar t1=timeNow();
    func(std::forward<Args>(args)...);
    return duration_cast<microseconds>(timeNow()-t1).count();
}

void printit(const string & str);
