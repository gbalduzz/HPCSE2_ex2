//
// Created by giovanni on 07.03.16.
//

#ifndef EX2_EXTENT_H
#define EX2_EXTENT_H
#include<hpx/hpx.hpp>
#include<vector>
using pairf=std::pair<float,float>;
using std::vector;
pairf bracket_MinMax(const vector<float> &x, const int start, const int end);

pairf MinMax(const vector<float>&  x,int N)
//parallel implementation
{
    const int n_threads=global_n_threads;
    std::vector<hpx::future<pairf>> futures(n_threads);
    const int block_size=N/n_threads;
    const int last_block=block_size+N%n_threads;
    for(int i=0;i<n_threads;i++){
        futures[i]=hpx::async(bracket_MinMax,x,i*block_size, (i==n_threads-1) ? block_size : last_block);
    }
    //compute global maximum
    pairf mm=futures[0].get();
    double min=mm.first;
    double max=mm.second;
    for(int i=1;i<n_threads;i++){
        mm=futures[i].get();
        if(mm.first<min) min=mm.first;
        if(mm.second>max) max=mm.second;
    }
    return pairf(min,max);
}
/*pairf MinMax(const vector<float>& x,const int N)
{
    hpx::future<pairf> ft=hpx::async(bracket_MinMax,x, 0,N/10);
    return  ft.get();
}*/

void extent(const int N, const vector<float>& x,const vector<float>& y,float& xmin,float& ymin,float& ext)
{
    pairf x_mm=MinMax(x,N);
    pairf y_mm=MinMax(y,N);
    xmin=x_mm.first;
    ymin=y_mm.first;
    float  dx(x_mm.second-x_mm.first);
    float  dy(y_mm.second-y_mm.first);
    ext= dx>dy ? dx : dy;
}

pairf bracket_MinMax(const vector<float> &x, const int start, const int size)
{
#if DEBUG
    assert(start>=0 && size+start<= x.size());
#endif
    double min(x[start]),max(x[start]);
    for(int i=start; i < start+size; i++) {
        if (x[i] > max) max = x[i];
        else if (x[i] < min) min = x[i];
    }
    return pairf(min,max);
}

#endif //EX2_EXTENT_H
