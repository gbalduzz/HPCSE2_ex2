//
// Created by giovanni on 09.03.16.
//
#include "../include/sort.h"
#include "../include/profiler.h"
#include<hpx/hpx.hpp>
#include<hpx/parallel/algorithms/sort.hpp>
#include<hpx/parallel/algorithms/for_each.hpp>
#include <hpx/parallel/execution_policy.hpp>
void sort(const int N,const vector<int>& index,vector<int>& keys)
{
  int i=0;
    hpx::parallel::for_each( hpx::parallel::v1::parallel_execution_policy(),
            keys.begin(),keys.end(),
        [&](int &k) {k = i; i++;}
    );

    //order the keys according to the relation between indexes
    hpx::parallel::sort( hpx::parallel::v1::parallel_vector_execution_policy(),
                         keys.begin(),keys.end(),
                         [&](const int& a, const int& b) {return (index[a] < index[b]);}
    );

}
