//
// Created by giovanni on 12.03.16.
//
#include<hpx/parallel/algorithms/for_each.hpp>
#include"../include/reorder.h"


void reorder(const int N, const vector<int>& keys, const vector<float> &x, const vector<float> &y, vector<float> &xsorted,
             vector<float> &ysorted)
{
    hpx::parallel::for_each( hpx::parallel::v1::parallel_execution_policy(),
                            std::begin(keys),std::end(keys),
                            [&](const int& k) {
                                int i=&k-&keys[0];
                                xsorted[i] = x[k];
                                ysorted[i] = y[k];
                            }
    );
}
