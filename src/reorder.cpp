//
// Created by giovanni on 12.03.16.
//
#include<hpx/parallel/algorithms/for_each.hpp>
#include"../include/reorder.h"


void reorder(const int N, const vector<int>& keys, const vector<float> &x, const vector<float> &y, vector<float> &xsorted,
             vector<float> &ysorted)
{
    int i(0);
    hpx::parallel::for_each( hpx::parallel::v1::parallel_execution_policy(),
                            std::begin(xsorted),std::end(xsorted),
                            [&](float &foo) {
                                xsorted[i] = x[keys[i]];
                                ysorted[i] = y[keys[i]];
                                i++;
                            }
    );
}
