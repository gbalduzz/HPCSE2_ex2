//
// Created by giovanni on 09.03.16.
//
#include "../include/sort.h"
#include "../include/profiler.h"
#include<hpx/hpx.hpp>
#include<hpx/parallel/algorithms/sort.hpp>
#include <hpx/parallel/execution_policy.hpp>
void sort(const int N,vector<int>& index,vector<int>& keys)
{
 #pragma omp parallel for num_threads(NUM_THREADS)
        for (int i = 0; i < N; i++) keys[i] = i;
    //order the keys according to the relation between indexes
    hpx::parallel::sort( hpx::parallel::v1::parallel_vector_execution_policy(),
                         keys.begin(),keys.end(),
                         [&](const int& a, const int& b) {return (index[a] < index[b]);}
    );

}
