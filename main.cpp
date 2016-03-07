#include <iostream>
#include <random>
#include "extent.h"
#include "morton.h"
#include "profiler.h"
using namespace std;
//the quadtree is a tree. Root is a square contiaining all the space. Each parent branch has 4 children.
// If there are twoo many particles in a leaf, branch it.
void InitializeAtRandom(flaot* x,float* y,int N);

int main() {
    const int N=1e7;
    float *x=new float[N];
    float *y=new float[N];
    InitializeAtRandom(x,y,N);

    {
        double xmin,ymin,ext;
        Profiler("Extend");
        extent(N,x,y,xmin,xmax,ext);
    }


    delete[] x; delete[] y;
}

void InitializeAtRandom(flaot* x,float* y,int N){
    std::mersenne_twister_engine mt(0);
    std::uniform_real_distribution rand(0,1);
    for(int i=0;i<N;i++){
        x[i]=rand(mt);
        y[i]=rand(mt);
    }
}