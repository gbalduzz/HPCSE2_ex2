//
// Created by giovanni on 09.03.16.
//
#include "../include/sort.h"
#include "../include/profiler.h"
#include<hpx/hpx.hpp>
#include<hpx/parallel/algorithms/sort.hpp>
#include<hpx/parallel/algorithms/for_each.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include"../include/parallel_for.h"

void sort(const int N,vector<int>& index,vector<int>& keys)
{
auto policy=hpx::parallel::par.with(hpx::parallel::static_chunk_size(100000));

    parallel_for(100000,N,
        [&](int i) {keys[i] =i;} 
    );

    //order the keys according to the relation between indexes
    hpx::parallel::sort( policy,
                         keys.begin(),keys.end(),
                         [&](const int& a, const int& b) {return (index[a] < index[b]);}
    );

}
