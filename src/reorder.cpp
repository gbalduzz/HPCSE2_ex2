//
// Created by giovanni on 12.03.16.
//
#include<hpx/parallel/algorithms/for_each.hpp>
#include"../include/reorder.h"
#include"../include/parallel_for.h"

void reorder(const int N, const vector<int>& keys, const vector<float> &x, const vector<float> &y, vector<float> &xsorted,
             vector<float> &ysorted)
{
    parallel_for( 100000,N,
                            [&](const int i) {
                                xsorted[i] = x[keys[i]];
                                ysorted[i] = y[keys[i]];
                            }
    );
}
