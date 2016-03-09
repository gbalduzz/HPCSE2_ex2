//const int global_n_threads=4;
#include <hpx/hpx.hpp>
#include <hpx/hpx.hpp>
#include <omp.h>
#include <iostream>
#include <random>
#include <assert.h>
#include "include/extent.h"
#include "include/morton.h"
#include "include/profiler.h"
#include "include/sort.h"
#include"include/reorder.h"
void InitializeAtRandom(vector<float>& x,vector<float>& y,int N);

int hpx_main() {
    static_assert(sizeof(int)==4,"Only 32 bits integeres are supported.");
    const int N=1e7;
    std::vector<float> x(N);
    std::vector<float> y(N);
    std::vector<float> xsorted(N);
    std::vector<float> ysorted(N);
    std::vector<int> index(N);
    std::vector<int> keys(N);
    InitializeAtRandom(x,y,N);

//can be changed by export OMP_NUM_THREADS=...
    std::cout<<"parallelizing over "<<NUM_THREADS<<" threads\n"<<std::endl;

    float xmin,ymin,ext;
    {
        Profiler p("Extend");
        extent(N,x,y,xmin,ymin,ext);
    }
    {
        Profiler p("Morton");
        morton(N,x,y,xmin,ymin,ext,index);
    }
    {
        Profiler p("Sort");
        sort(N,index,keys);
    }
    {
        Profiler p("Reorder");
        reorder(N,keys,x,y,xsorted,ysorted);
    }


    return hpx::finalize();
}

int main(int argc,char**argv)
{
return hpx::init(argc,argv);
}

void InitializeAtRandom(vector<float>& x,vector<float>& y,int N){
    std::mt19937_64 mt(0);
    std::uniform_real_distribution<float> rand(0,1);
    for(int i=0;i<N;i++){
        x[i]=rand(mt);
        y[i]=rand(mt);
    }
}
