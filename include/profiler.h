//
// Created by giovanni on 07.03.16.
//
#ifndef EX2_PROFILER_H
#define EX2_PROFILER_H
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <iostream>

class Profiler{
public:
    Profiler(std::string n0="");
    inline ~Profiler();
private:
    std::string name;
    timespec t0,t1;
    long int elapsed();
};

Profiler::Profiler(std::string n0):name(n0){
        clock_gettime(CLOCK_MONOTONIC, &t0);
}

inline Profiler::~Profiler() {
    clock_gettime(CLOCK_MONOTONIC, &t1);
    std::cout<<"function "<<name<<" took "<<elapsed()<< " ns to complete"<<std::endl;
}

long int Profiler::elapsed() {
    return (long int) (t1.tv_nsec-t0.tv_nsec)+(t1.tv_sec-t0.tv_sec)*1e9;
}

#endif //EX2_PROFILER_H
