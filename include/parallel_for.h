//
// Created by giovanni on 14.03.16.
//

#ifndef HPCSE2_EX2_PARALLEL_FOR_H
#define HPCSE2_EX2_PARALLEL_FOR_H
#include<hpx/hpx.hpp>
#include <vector>
using std::vector;
using hpx::future;

template<class F>
void do_chunk(int i0,int imax,F);

template<class F>
void parallel_for(const int chunk_size,const int N,F f)
{
    int n_tasks=(N+chunk_size-1)/chunk_size;
    vector<future<void>> vf(n_tasks);
    for(int i=0;i<n_tasks;i++) vf[i]=hpx::async(do_chunk<F>,i*chunk_size,std::min(N,(i+1)*chunk_size),f);
    //for(int i=0;i<n_tasks;i++) vf[i]=hpx::async(do_chunk,i*chunk_size,(i+1)*chunk_size,f);
    hpx::wait_all(vf);
}

template<class F>
void do_chunk(int i0,int imax,F f)
{
    for(int i=i0;i<imax;i++) f(i);
}

#endif //HPCSE2_EX2_PARALLEL_FOR_H
