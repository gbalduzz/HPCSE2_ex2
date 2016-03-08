#include <iostream>
#include <random>
#include <assert.h>
#include "extent.h"
#include "morton.h"
#include "profiler.h"
#include "sort.h"
//TOME the quadtree is a tree. Root is a square containing all the space. Each parent branch has 4 children.
// If there more then k particles in a leaf, branch it.
void InitializeAtRandom(float* x,float* y,int N);

int main() {
    assert(sizeof(int)==4);
    const int N=1e5;
    float *x=new float[N];
    float *y=new float[N];
    int *index=new int[N];
    InitializeAtRandom(x,y,N);

    float xmin,ymin,ext;
    {
        Profiler("Extend");
        extent(N,x,y,xmin,ymin,ext);
    }
    {
        Profiler("Morton");
        morton(N,x,y,xmin,ymin,ext,index);
    }


    delete[] x; delete[] y; delete[] index;
}

void InitializeAtRandom(float* x,float* y,int N){
    std::mt19937_64 mt(0);
    std::uniform_real_distribution<float> rand(0,1);
    for(int i=0;i<N;i++){
        x[i]=rand(mt);
        y[i]=rand(mt);
    }
}