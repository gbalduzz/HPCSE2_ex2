//const int global_n_threads=4;
#define VERBOSE
#include <hpx/hpx.hpp>
#include <hpx/hpx.hpp>
#include <iostream>
#include <random>
#include <assert.h>
#include "include/extent.h"
#include "include/morton.h"
#include "include/profiler.h"
#include "include/sort.h"
#include"include/reorder.h"
using std::cout; using std::endl;
void InitializeAtRandom(vector<float>& x,vector<float>& y,int N);
using std::vector;
int hpx_main(int argc,char** argv) {
    static_assert(sizeof(int)==4,"Only 32 bits integeres are supported.");
    const int N_default=1e7;
    int N= (argc>1) ? std::atoi(argv[1]) : N_default;
    cout<<"Size: "<<N<<endl;
    std::vector<float> x(N);
    std::vector<float> y(N);
    std::vector<float> xsorted(N);
    std::vector<float> ysorted(N);
    std::vector<int> index(N);
    std::vector<int> keys(N);
    InitializeAtRandom(x,y,N);


//can be changed by export OMP_NUM_THREADS=...
    std::cout<<"parallelizing over "<<hpx::get_os_thread_count() <<" threads\n"<<std::endl;

    float xmin,ymin,ext;
    {
        Profiler p("Extend");
        extent(N,x,y,xmin,ymin,ext);
    }
    vector<int> ind2(N);
    {
        Profiler p("Morton");
        morton(N,x,y,xmin,ymin,ext,index);
    }
    morton(N,x,y,xmin,ymin,ext,ind2);
    for (int i=0;i<N;i++) assert(index[i]==ind2[i]);
    {
        Profiler p("Sort");
        sort(N,index,keys);
    }
    vector<int> k2(N);
    sort(N,ind2,k2);
    {
        Profiler p("Reorder");
        reorder(N,keys,x,y,xsorted,ysorted);
    }
    vector<float> xs2(N);
    reorder(N,k2,x,y,xs2,ysorted);
    for (int i=0;i<N;i++) assert(xsorted[i]==xs2[i]);

#ifdef VERBOSE
    
    std::cout<<"\nThe first 5 x/y are:\n";
    for(int i=0;i<5;i++) std::cout<<xsorted[i]<<"\t"<<ysorted[i]<<std::endl;
#endif
    
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
